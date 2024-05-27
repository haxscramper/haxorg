#include "test_editor_model.hpp"

void TestEditorModel::testSubtreeEditing() {
    QTemporaryDir dir;
    AppState      state;
    add_file(
        state,
        dir,
        "main.org",
        "First paragraph in document\n\nSecond paragraph in document");

    auto window = init_window(state);
    auto s      = window->store.get();
    window->resize(300, 300);
    window->loadFiles();

    OrgDocumentEdit* edit = dynamic_cast<OrgDocumentEdit*>(
        window->findChild<OrgDocumentEdit*>(
            "MainWindow-OrgDocumentEdit-0"));

    QVERIFY(edit);

    auto index = edit->model()->index(0, 0, edit->model()->index(0, 0));
    QVERIFY(index.isValid());
    edit->setFocus();
    QVERIFY(QTest::qWaitForWindowActive(window.get()));
    QCOMPARE_EQ(edit->model()->rowCount(), 1);

    auto dfs_before = dfs_boxes(edit->docModel->root);

    { // Verify the original structure of the document read from the
      // text
        auto r = edit->docModel->root;
        QCOMPARE_EQ(r->parent, nullptr);
        QCOMPARE_EQ(r->subnodes.size(), 2);
        QVERIFY(node(s, r)->is(osk::Document));
        QVERIFY(node(s, r->at(0))->is(osk::Paragraph));
        QVERIFY(node(s, r->at(1))->is(osk::Paragraph));
        auto n = node(s, index);
        QVERIFY(n->is(osk::Paragraph));
        QCOMPARE_EQ(str(n), "First paragraph in document");
        auto tree = edit->docModel->toNode();

        QCOMPARE_EQ(
            format(tree),
            "First paragraph in document\n\nSecond paragraph in "
            "document");
    }


    { // Double-click on the editor cell and enter some text
        trigger_editor_of(edit, index);

        QTest::qWait(100);

        QApplication::processEvents();

        QTextEdit* focusedWidget = qobject_cast<QTextEdit*>(
            QApplication::focusWidget());
        QVERIFY(focusedWidget);
        QTest::keyClicks(focusedWidget, "your text here ");
        trigger_editor_complete(edit, index);
        QTest::qWait(5);
    }

    auto dfs_after = dfs_boxes(edit->docModel->root);


    { // After editing operations only a single element in the model
      // should change the boxed node value.
        QCOMPARE_EQ(dfs_before.size(), dfs_after.size());
        QCOMPARE_EQ(dfs_before.size(), 3);
        QCOMPARE_EQ(dfs_before.at(0), dfs_after.at(0));
        QCOMPARE_NE(dfs_before.at(1), dfs_after.at(1));
        QCOMPARE_EQ(dfs_before.at(2), dfs_after.at(2));

        // The store does not replace the content of the original boxed
        // node -- it creates an entirely new node and puts it into the
        // store. This way it is still possible to access all the
        // previous building blocks of the document.
        QCOMPARE_EQ(
            format(s->getBoxedNode(dfs_before.at(1))),
            "First paragraph in document");
        QCOMPARE_EQ(
            format(s->getBoxedNode(dfs_after.at(1))),
            "your text here First paragraph in document");
    }

    {
        auto n = node(s, index);
        QVERIFY(n->is(osk::Paragraph));
        QCOMPARE_EQ(str(n), "your text here First paragraph in document");
        auto tree = edit->docModel->toNode();
        QCOMPARE_EQ(
            format(tree),
            "your text here First paragraph in document\n\nSecond "
            "paragraph in document");
    }
}

void TestEditorModel::testOutlineJump() {
    QTemporaryDir dir;
    AppState      state;
    add_file(state, dir, "main.org", R"(
* First subtree

First subtree paragraph 1

First subtree paragraph 2

** First subtree subtree 1

First subtree subtree 1 paragraph 1

First subtree subtree 1 paragraph 2

** First subtree subtree 2

First subtree subtree 2 paragraph 1

First subtree subtree 2 paragraph 2

* Second subtree

Second subtree paragraph 1

Second subtree paragraph 2

* Third subtree

Third subtree paragraph 1

Third subtree paragraph 2

)");

    auto window = init_window(state);
    auto s      = window->store.get();
    window->loadFiles();

    OrgDocumentOutline* outline = dynamic_cast<OrgDocumentOutline*>(
        window->findChild<OrgDocumentOutline*>(
            "MainWindow-OrgDocumentOutline"));

    OrgDocumentEdit* edit = dynamic_cast<OrgDocumentEdit*>(
        window->findChild<OrgDocumentEdit*>(
            "MainWindow-OrgDocumentEdit-0"));

    QVERIFY(outline);
    QVERIFY(edit);

    { // Text outline model structure
        auto m = outline->model();
        QCOMPARE_EQ(m->rowCount(), 1);
        {
            auto r   = m->index(0, 0);
            auto t1  = m->index(0, 0, r);
            auto t11 = m->index(0, 0, t1);
            auto t12 = m->index(1, 0, t1);
            QVERIFY(node(s, r)->is(osk::Document));
            QVERIFY(r.isValid());
            QCOMPARE_EQ(m->rowCount(r), 3);

            QVERIFY(t1.isValid());
            QVERIFY(t11.isValid());
            QVERIFY(t12.isValid());
            QCOMPARE_EQ(m->rowCount(t1), 2);
            QCOMPARE_EQ(m->rowCount(t11), 0);
            QCOMPARE_EQ(m->rowCount(t12), 0);
            QCOMPARE_EQ(node(s, t1).getAs<sem::Subtree>()->level, 1);
            QCOMPARE_EQ(node(s, t11).getAs<sem::Subtree>()->level, 2);
            QCOMPARE_EQ(node(s, t12).getAs<sem::Subtree>()->level, 2);
        }
    }

    { // Text edit model structure
        auto m = edit->model();
        QCOMPARE_EQ(m->rowCount(), 1);
        // 'First subtree' has two nested paragraphs and two nested
        // sub-subtrees, each one having two paragraphs of their own.
        // Outline model filters all non-subtree elements so it should
        // have only two subtrees under t1 and no sub-sub-nodes under
        // t11 and t12.
        {
            auto r   = m->index(0, 0);
            auto t1  = m->index(0, 0, r);
            auto t11 = m->index(2, 0, t1);
            auto t12 = m->index(3, 0, t1);
            QCOMPARE_EQ(m->rowCount(t1), 4);
            QCOMPARE_EQ(m->rowCount(t11), 2);
            QCOMPARE_EQ(m->rowCount(t12), 2);
        }
    }

    { // Trigger navigation double click
        auto       outline_model = outline->model();
        auto       edit_model    = edit->model();
        QSignalSpy spy{edit, SIGNAL(focusedOn(QModelIndex))};

        QTest::mouseDClick(
            outline->viewport(),
            Qt::LeftButton,
            Qt::NoModifier,
            outline->visualRect(outline_model->index(0, 0)).center());

        QTest::qWait(100);
        QCOMPARE_EQ(spy.count(), 1);
        QList<QVariant> arguments = spy.takeFirst();
        QCOMPARE_EQ(
            arguments.at(0).value<QModelIndex>(), edit_model->index(0, 0));
    }

    { // Test the rest of the outline jump mappings
        auto outline_model = outline->model();
        auto edit_model    = edit->model();
        auto p00           = std::make_pair(0, 0);
        for (auto const& [path_outline, path_edit] :
             Vec<Pair<Vec<Pair<int, int>>, Vec<Pair<int, int>>>>{
                 // List of model index paths in both outlines
                 {
                     // Frist first toplevel tree in the outline to the
                     // first toplevel tree in the editor.
                     {p00, p00},
                     {p00, p00},
                 },
                 {
                     // First-First toplevel to the first-first outline
                     // should account for paragraph offsets.
                     {p00, p00, std::make_pair(1, 0)},
                     {p00, p00, std::make_pair(3, 0)},
                 },
                 {
                     {p00, std::make_pair(2, 0)},
                     {p00, std::make_pair(2, 0)},
                 },
             }) {
            edit->scrollTo(
                edit->model()->index(0, 0),
                QAbstractItemView::PositionAtTop);
            QSignalSpy spy{edit, SIGNAL(focusedOn(QModelIndex))};
            auto       outline_index = getAtQModelPath(
                outline_model, path_outline);
            auto edit_index = getAtQModelPath(edit_model, path_edit);
            QVERIFY(outline_index.isValid());
            QVERIFY(edit_index.isValid());

            QTest::mouseDClick(
                outline->viewport(),
                Qt::LeftButton,
                Qt::NoModifier,
                outline->visualRect(outline_index).center());

            QTest::qWait(100);
            QCOMPARE_EQ(spy.count(), 1);
            QList<QVariant> arguments = spy.takeFirst();
            QCOMPARE_EQ(arguments.at(0).value<QModelIndex>(), edit_index);
        }
    }
}

void TestEditorModel::testParagraphMovements() {
    QTemporaryDir dir;
    AppState      state;
    Str           nl{"\n\n"};
    Str           p1{"First paragraph in document"};
    Str           p2{"Second paragraph in document"};
    Str           p3{"Third paragraph in document"};

    add_file(state, dir, "main.org", p1 + nl + p2 + nl + p3);


    auto window = init_window(state);
    window->resize(300, 300);
    window->loadFiles();

    OrgDocumentEdit* edit = dynamic_cast<OrgDocumentEdit*>(
        window->findChild<OrgDocumentEdit*>(
            "MainWindow-OrgDocumentEdit-0"));

    auto get       = [&]() { return edit->docModel->toNode(); };
    auto root      = edit->model()->index(0, 0);
    auto par_index = [&](int index) {
        return edit->model()->index(index, 0, root);
    };

    auto par_text = [&](int row) {
        return str(node(edit->docModel->store, par_index(row)));
    };

    { // Moving paragraph outside of the document boundary is ignored
        auto i0 = edit->model()->index(0, 0, root);


        edit->movePositionUp(i0, 0);
        QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);

        edit->movePositionUp(i0, 200);
        QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);

        auto i2 = edit->model()->index(2, 0, root);
        edit->movePositionDown(i2, 0);
        QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);

        edit->movePositionDown(i2, 200);
        QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);
    }

    // debug_tree(edit->model(), edit->docModel->store);

    { // Move first paragraph down and back up
        // debug_tree(edit->model(), edit->docModel->store);
        edit->movePositionDown(edit->model()->index(0, 0, root), 1);
        // debug_tree(edit->model(), edit->docModel->store);

        QCOMPARE_EQ(format(get()), p2 + nl + p1 + nl + p3);
        QCOMPARE_EQ(par_text(0), p2);
        QCOMPARE_EQ(par_text(1), p1);
        QCOMPARE_EQ(par_text(2), p3);

        edit->movePositionUp(edit->model()->index(1, 0, root), 1);
        QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);
        QCOMPARE_EQ(par_text(0), p1);
        QCOMPARE_EQ(par_text(1), p2);
        QCOMPARE_EQ(par_text(2), p3);
    }

    { // Move first paragraph all the way down and then back again
        edit->movePositionDown(edit->model()->index(0, 0, root), 2);
        QCOMPARE_EQ(format(get()), p2 + nl + p3 + nl + p1);
        QCOMPARE_EQ(par_text(0), p2);
        QCOMPARE_EQ(par_text(1), p3);
        QCOMPARE_EQ(par_text(2), p1);

        edit->movePositionUp(edit->model()->index(2, 0, root), 2);
        QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);
        QCOMPARE_EQ(par_text(0), p1);
        QCOMPARE_EQ(par_text(1), p2);
        QCOMPARE_EQ(par_text(2), p3);
    }


    QVERIFY(edit);
}

void TestEditorModel::testSubtreeDemotion() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "First"),
        getSubtree(1, "Second"),
    }));

    QVERIFY(edit);

    auto t = api.getAt<sem::Subtree>();

    auto compare_no_change = [&]() {
        QCOMPARE_EQ((api.getNode({0, 0})->getKind()), osk::Subtree);
        QCOMPARE_EQ((api.getNode({0, 0})->getKind()), osk::Subtree);
        QCOMPARE_EQ((api.str(t({0, 0})->title)), "First");
        QCOMPARE_EQ((api.str(t({0, 1})->title)), "Second");
        QCOMPARE_EQ((t({0, 0})->subnodes.size()), 0);
        QCOMPARE_EQ((t({0, 1})->subnodes.size()), 0);
        QCOMPARE_EQ((t({0, 0})->level), 1);
        QCOMPARE_EQ((t({0, 1})->level), 1);
        auto tree1 = getFile({
            getSubtree(1, "First"),
            getSubtree(1, "Second"),
        });
        QCOMPARE_EQ(api.getFormat(), tree1);
    };

    compare_no_change();
    edit->demoteSubtreeRecursive(api.getIndex({0, 1}), 0);
    compare_no_change();
    edit->promoteSubtreeRecursive(api.getIndex({0, 1}), 20);
    compare_no_change();

    // debug_tree(edit->model(), edit->docModel->store);
    edit->demoteSubtreeRecursive(api.getIndex({0, 1}), 1);
    // debug_tree(edit->model(), edit->docModel->store);

    {
        QCOMPARE_EQ((api.getNode({0, 0})->getKind()), osk::Subtree);
        QCOMPARE_EQ((api.getNode({0, 0, 0})->getKind()), osk::Subtree);
        QCOMPARE_EQ((api.str(t({0, 0})->title)), "First");
        QCOMPARE_EQ((api.str(t({0, 0, 0})->title)), "Second");
        QCOMPARE_EQ((t({0, 0})->subnodes.size()), 1);
        QCOMPARE_EQ((t({0, 0, 0})->subnodes.size()), 0);
        QCOMPARE_EQ((t({0, 0})->level), 1);
        QCOMPARE_EQ((t({0, 0, 0})->level), 2);

        auto tree = getFile({
            getSubtree(1, "First"),
            "",
            getSubtree(2, "Second"),
        });

        QCOMPARE_EQ(api.getFormat(), tree);
    }
}

void TestEditorModel::testTestDocumentModel() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "tree1"),
        getSubtree(1, "tree2"),
        getSubtree(1, "tree3"),
    }));

    QVERIFY(edit);

    auto              t = api.getAt<sem::Subtree>();
    TestDocumentModel m;

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
            m.tree("tree2"),
            m.tree("tree3"),
        }));
}

void TestEditorModel::testRecursiveDemoteLastSubtreeInDocument() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "tree1"),
        getSubtree(1, "tree2"),
        getSubtree(1, "tree3"),
    }));

    QVERIFY(edit);

    auto              t = api.getAt<sem::Subtree>();
    TestDocumentModel m;

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
            m.tree("tree2"),
            m.tree("tree3"),
        }));

    edit->demoteSubtreeRecursive(api.getIndex({0, 2}));

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
            m.tree("tree2", {m.tree("tree3")}),
        }));
}

void TestEditorModel::testRecursiveDemoteMiddleSubtreeInDocument() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "tree1"),
        getSubtree(1, "tree2"),
        getSubtree(1, "tree3"),
    }));

    QVERIFY(edit);

    auto              t = api.getAt<sem::Subtree>();
    TestDocumentModel m;

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
            m.tree("tree2"),
            m.tree("tree3"),
        }));

    edit->demoteSubtreeRecursive(api.getIndex({0, 1}));

    m.compare(
        api,
        m.document({
            m.tree("tree1", {m.tree("tree2")}),
            m.tree("tree3"),
        }));
}

void TestEditorModel::testRecursiveDemoteSubtreeBlock1() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "tree1"),
        getSubtree(1, "tree2"),
        getSubtree(2, "tree3"),
    }));

    QVERIFY(edit);

    auto              t = api.getAt<sem::Subtree>();
    TestDocumentModel m;

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
            m.tree("tree2", {m.tree("tree3")}),
        }));

    edit->demoteSubtreeRecursive(api.getIndex({0, 1}));

    m.compare(
        api,
        m.document({
            m.tree("tree1", {m.tree("tree2", {m.tree("tree3")})}),
        }));
}

void TestEditorModel::testRecursiveDemoteSubtreeBlock7() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "tree1"),
        getSubtree(1, "tree2"),
        getSubtree(2, "tree3"),
        getSubtree(3, "tree4"),
        getSubtree(4, "tree5"),
        getSubtree(5, "tree6"),
        getSubtree(6, "tree7"),
        getSubtree(7, "tree8"),
    }));

    QVERIFY(edit);

    auto              t = api.getAt<sem::Subtree>();
    TestDocumentModel m;

    m.compare(
        api,
        m.document(
            {m.tree("tree1"),
             m.tree(
                 "tree2",
                 {m.tree(
                     "tree3",
                     {m.tree(
                         "tree4",
                         {m.tree(
                             "tree5",
                             {m.tree(
                                 "tree6",
                                 {m.tree(
                                     "tree7",
                                     {m.tree("tree8")})})})})})})}));

    edit->demoteSubtreeRecursive(api.getIndex({0, 1}));

    m.compare(
        api,
        m.document({m.tree(
            "tree1",
            {m.tree(
                "tree2",
                {m.tree(
                    "tree3",
                    {m.tree(
                        "tree4",
                        {m.tree(
                            "tree5",
                            {m.tree(
                                "tree6",
                                {m.tree(
                                    "tree7",
                                    {m.tree("tree8")})})})})})})})}));
}

void TestEditorModel::testInsertBelow() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "tree1"),
    }));

    auto tree = api.tree({0});

    // debug_tree(edit->model(), edit->docModel->store);

    auto em = edit->model();
    {
        QCOMPARE_EQ(em->rowCount(), 1);
        auto doc = em->index(0, 0);
        QVERIFY(doc.isValid());
        QCOMPARE_EQ(em->rowCount(doc), 1);
    }


    TestDocumentModel m;

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
        }));

    tree->apply(
        tree->getInsertAfter(),
        window->store->toRoot(sem::parseString("* Inserted")->at(0)));

    {
        QCOMPARE_EQ(em->rowCount(), 1);
        auto doc = em->index(0, 0);
        QVERIFY(doc.isValid());
        QCOMPARE_EQ(em->rowCount(doc), 2);
    }

    // debug_tree(edit->model(), edit->docModel->store);

    auto r = window->store->getRoot(0);

    QCOMPARE_EQ(r->subnodes.size(), 2);
    QCOMPARE_NE(r->subnodes.at(0).get(), nullptr);
    QCOMPARE_NE(r->subnodes.at(1).get(), nullptr);

    QCOMPARE_EQ(r->subnodes.at(0)->parent, r);
    QCOMPARE_EQ(r->subnodes.at(1)->parent, r);

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
            m.tree("Inserted"),
        }));
}

void TestEditorModel::testInsertAbove() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "tree1"),
    }));

    auto tree = api.tree({0});

    TestDocumentModel m;

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
        }));

    tree->apply(
        tree->getInsertBefore(),
        window->store->toRoot(sem::parseString("* Inserted")->at(0)));

    m.compare(
        api,
        m.document({
            m.tree("Inserted"),
            m.tree("tree1"),
        }));

    tree->apply(
        tree->getInsertBefore(),
        window->store->toRoot(sem::parseString("* Inserted2")->at(0)));

    m.compare(
        api,
        m.document({
            m.tree("Inserted"),
            m.tree("Inserted2"),
            m.tree("tree1"),
        }));

    tree->apply(
        tree->getInsertBefore(),
        window->store->toRoot(sem::parseString("* Inserted3")->at(0)));

    m.compare(
        api,
        m.document({
            m.tree("Inserted"),
            m.tree("Inserted2"),
            m.tree("Inserted3"),
            m.tree("tree1"),
        }));
}

void TestEditorModel::testInsertFirstUnder() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "tree1"),
    }));

    auto tree = api.tree({0});

    TestDocumentModel m;

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
        }));

    tree->apply(
        tree->getInsertFirstUnder(),
        window->store->toRoot(sem::parseString("** Inserted")->at(0)));

    m.compare(
        api,
        m.document({
            m.tree(
                "tree1",
                {
                    m.tree("Inserted"),
                }),
        }));

    tree->apply(
        tree->getInsertFirstUnder(),
        window->store->toRoot(sem::parseString("** Inserted2")->at(0)));

    m.compare_structure(
        api,
        m.document({
            m.tree(
                "tree1",
                {
                    m.tree("Inserted2"),
                    m.tree("Inserted"),
                }),
        }));

    tree->apply(
        tree->getInsertFirstUnder(),
        window->store->toRoot(sem::parseString("** Inserted3")->at(0)));

    m.compare_structure(
        api,
        m.document({
            m.tree(
                "tree1",
                {
                    m.tree("Inserted3"),
                    m.tree("Inserted2"),
                    m.tree("Inserted"),
                }),
        }));
}

void TestEditorModel::testInsertLastUnder() {
    auto [window, edit, api] = init_test_for_file(getFile({
        getSubtree(1, "tree1"),
    }));

    auto tree = api.tree({0});

    TestDocumentModel m;

    m.compare(
        api,
        m.document({
            m.tree("tree1"),
        }));

    tree->apply(
        tree->getInsertLastUnder(),
        window->store->toRoot(sem::parseString("** Inserted")->at(0)));

    m.compare(
        api,
        m.document({
            m.tree(
                "tree1",
                {
                    m.tree("Inserted"),
                }),
        }));

    tree->apply(
        tree->getInsertLastUnder(),
        window->store->toRoot(sem::parseString("** Inserted2")->at(0)));

    m.compare_structure(
        api,
        m.document({
            m.tree(
                "tree1",
                {
                    m.tree("Inserted"),
                    m.tree("Inserted2"),
                }),
        }));

    tree->apply(
        tree->getInsertLastUnder(),
        window->store->toRoot(sem::parseString("** Inserted3")->at(0)));

    m.compare_structure(
        api,
        m.document({
            m.tree(
                "tree1",
                {
                    m.tree("Inserted"),
                    m.tree("Inserted2"),
                    m.tree("Inserted3"),
                }),
        }));
}

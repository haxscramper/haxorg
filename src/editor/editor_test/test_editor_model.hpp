#pragma once
#include "test_utils.hpp"

class TestEditorModel
    : public QObject
    , public TestBase {
    Q_OBJECT

  private slots:
    void initTestCase() { init_test_base(); }
    void cleanupTestCase() { cleanup_test_base(); }

    void testSubtreeEditing();
    void testOutlineJump();
    void testParagraphMovements();
    void testSubtreeDemotion();
    void testTestDocumentModel();

    void testRecursiveDemoteLastSubtreeInDocument();
    void testRecursiveDemoteMiddleSubtreeInDocument();
    void testRecursiveDemoteSubtreeBlock1();
    void testRecursiveDemoteSubtreeBlock7();

    void testInsertBelow();
    void testInsertAbove();
    void testInsertFirstUnder();
    void testInsertLastUnder();
};

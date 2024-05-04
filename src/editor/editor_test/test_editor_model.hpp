#pragma once
#include "test_utils.hpp"

class TestEditorModel : public QObject {
    Q_OBJECT

  private slots:
    void testSubtreeEditing();
    void testOutlineJump();
    void testParagraphMovements();
    void testSubtreePromotion();
};

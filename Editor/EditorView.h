#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QDockWidget>

namespace Ui {
class EditorView;
}

class EditorView : public QDockWidget
{
    Q_OBJECT

public:
    explicit EditorView(QWidget *parent = nullptr);
    ~EditorView();

private:
    Ui::EditorView *ui;
};

#endif // EDITORVIEW_H

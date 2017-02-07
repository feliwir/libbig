#pragma once
#include <QMainWindow>
#include <QTreeView>
#include <QAction>
#include <QLabel>
#include <libbig/big.hpp>
using namespace libbig;

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(QWidget *parent = 0);
	~Editor();

	void Load(const std::string& name);
protected:
	#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU
private slots:
	void newFile();
	void open();
	void save();
	void saveAs();
	void undo();
	void redo();
	void cut();
	void copy();
	void paste();
	void about();
	void aboutQt();
	void exit();
private:
	void createActions();
	void createMenus();

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *formatMenu;
	QMenu *helpMenu;
	QActionGroup *alignmentGroup;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;
	QAction *undoAct;
	QAction *redoAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *aboutAct;
	QAction *aboutQtAct;
private:
	QTreeView m_treeview;
	std::map<QString, Big> m_archives;
};
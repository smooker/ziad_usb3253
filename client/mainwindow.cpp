#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("ZIAD USB3253"));

    QWidget *fake = new QWidget();

    QGridLayout *gl = new QGridLayout();
    fake->setLayout(gl);

    list = new QList<QCheckBox*>;

    for(int i=0; i<8; i++) {
        list->append(new QCheckBox(QString("DO%1").arg(i)));
        gl->addWidget(list->last(), i, 0, 1, 1);
        list->last()->setProperty("id", QVariant(i));
        connect(list->last(), SIGNAL(clicked(bool)), this, SLOT(cbClicked(bool)));
    }

    setCentralWidget(fake);
}

MainWindow::~MainWindow()
{

}

void MainWindow::cbClicked(bool enable_in)
{
    qDebug() << static_cast<QCheckBox*>(sender())->property("id");
    qDebug() << static_cast<QCheckBox*>(sender())->isChecked();
}

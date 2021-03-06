#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QtUiTools/QUiLoader>

#include "renderer.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    QString filename = QString::fromLocal8Bit( argv[1] );
    QUiLoader loader;
    QFile f( filename );
    if ( !f.open(QIODevice::ReadOnly) )
	return 1;

    QWidget *ui = loader.load( &f );
    if ( !ui )
	return 1;

    QString pdfFile = filename.remove(".ui");
    pdfFile = pdfFile.append(".pdf");
    
    Renderer render;
    render.setTarget(ui);
    render.setPdfFile(pdfFile);
    QTimer::singleShot( 1000, &render, SLOT(start()));

    ui->show();
    app.exec();
}

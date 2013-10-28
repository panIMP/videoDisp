#include <QApplication>
#include "videodisp.h"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);
    videoDisp disp;
    disp.show();
    return app.exec();
}

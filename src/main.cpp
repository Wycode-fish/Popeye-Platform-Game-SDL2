#include "../include/mainprogram.h"

int main( int argc, char* argv[] ){
    //cout << "Working Directory : " << args[1] << endl;
    //QApplication app(argc, argv);

    MainProgram::getInstance()->run();
    return 0;
}

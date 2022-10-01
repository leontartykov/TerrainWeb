#include "app_command.h"
#include "../../gui/main_window.h"

BaseAppCommand::~BaseAppCommand() {}

void LaunchAppCmd::execute(){
    this->_execute();
}

int LaunchAppCmd::_execute()
{
    int argc = 1;
    std::cout << "Launch execute." << std::endl;
    char *argv[] = {"/home/lev/Desktop/study/semester_6/iu7_software_design_labs_2022/src/build-ppo_cg_course-Desktop-Release/core_files"};
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    /*std::unique_ptr<QProcess> process;
    process = std::unique_ptr<QProcess>(new QProcess());

    QString program = "/home/lev/Рабочий стол/study/semester_5/bmstu_cg_course_project/build-cg_course-Desktop-Release/bmstu_cg_course_project";

    process->startDetached(program, QStringList() << "");
    process->waitForFinished(-1);*/
}

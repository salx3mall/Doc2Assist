/*Doc2Assist is the application for changing the format of tests representation from numeric list like
  ____________________________________________________________________________________
  1. Text of qeustion #1
  A. Correct answer
  B. Incorrect answer...
  ____________________________________________________________________________________
  In the format that is understood to the testing application Assistant, developed for medical students of Sumy State University
  ____________________________________________________________________________________
  ?
  Text of quesstion #1
  + Correct answer
  - Incorrect answer...
  ____________________________________________________________________________________
  All the output information is written in russian since this application is intended for the russian-speaking users.
  This project made me understand, what the unicode is and how and why to work with the wide character instead of ordinary ones.
*/

#include <clocale>
#include "FileManipulators.h"

using namespace std;

void greetUser();

int main() {
    greetUser();

    wstring fileName;
    while (true) {
        fileName = getNewFileName();
        if (fileName.empty())
            break;
	    processSingleFile(fileName);
    }
    cout << "  Спасибо, что воспользовались нашим продуктом!" << endl;

    system("pause");
    return 0;
}



void greetUser() {
    setlocale(LC_ALL, "Russian");

    cout << "  Привет, пользователь!" << endl;
    cout << "  Программа Doc2Assist предназначена для преобразования нумерованного списка те" << "\n" <<
            "стов в формат, понятный программе Assist от мед. института СумГУ."               << endl;
    cout << "  Входной формат следующий: \"[номер]. [текст][перенос строки]\" или \"[номер]." << "\n" <<
            "[табуляция][текст][перенос строки]\". Посмотреть примеры формата можно в файле"  << "\n" <<
            "example.txt, находящемся в каталоге tests."                                      << endl;
    cout << "  Прежде чем продолжить работу, посетите этот каталог и поместите в него нужное" << "\n" <<
            "количество файлов, содержащих необходимые Вам тематические блоки тестов - один"  << "\n" <<
            "файл на один блок тестов. Лучше всего сразу дать файлам осмысленные имена."      << endl;
    cout << "  Каждый файл обязательно должен иметь расширение .txt, иначе программа просто"  << "\n" <<
            "не найдет файлы. Можно размножить файл example.txt, переименовывая файлы и вста" << "\n" <<
            "вляя в них нужный текст. После того, как это будет выполнено, нажмите клавишу"   << "\n" <<
            "Enter, чтобы запустить процесс обработки."                                       << endl;
    cout << "  Результаты будут помещены в папку results (во избежание проблем, пожалуйста,"  << "\n" <<
            "не удаляйте её). Выходные файлы имеют то же название, что и входные, но другое"  << "\n" <<
            "расширение - .qst. При создании выходного файла в папке results, файл с тем же"  << "\n" <<
            "именем будет перезаписан."                                                       << endl;
    cout << "  Важно: верным вариантом ответа обязательно должен быть вариант А! При этом уд" << "\n" <<
            "аляется звездочка в конце строки."                                               << endl;

    system("pause");
}

#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <Windows.h>
#include <clocale>
#include "StringProcessingFunctions.h"

using namespace std;

wstring getNewFileName() {
    setlocale(LC_ALL, "Russian");

    static bool firstFile = true;

    static WIN32_FIND_DATA findData;
    static HANDLE handle = INVALID_HANDLE_VALUE;

    if (firstFile) {
        handle = FindFirstFile(L"./tests/*.txt", &findData);
        if (handle == INVALID_HANDLE_VALUE) {
            cout << "  Не найдено файлов с расширением '.txt'. Обработка завершена." << endl;
            return L"";
        }
        firstFile = false;
    }
    else {
        FindNextFile(handle, &findData);
        if (GetLastError() == ERROR_NO_MORE_FILES) {
            cout << "  Больше нет файлов с нужным расширением. Обработка завершена." << endl;
            return L"";
        }
    }

    return findData.cFileName;
}

void processSingleFile(wstring fileName) {
    setlocale(LC_ALL, "Russian");

    static wifstream tests;
    static wofstream result;

    if (tests.is_open())
        tests.close();
    if (result.is_open())
        result.close();

    tests.open(L"./tests/" + fileName);
    if (tests.is_open()) {
        wstring resultFileName = L"./results/" + transformFileExtension(fileName);

        result.open(resultFileName);
        if (!result.is_open()) {
            wcout << L"  Не удалось создать или открыть файл " << transformFileExtension(fileName)      << "\n" <<
                     L"в папке results. Если он открыт в редакторе, закройте файл и повторите попытку." << "\n" <<
                     L"Результаты преобразования соответствующего блока тестов не сохранены, увы."      << endl;
            return;
        }

        wstring currentString;

        getline(tests, currentString);

        if (iswdigit(currentString[0])) {
            currentString.erase(currentString.find_last_not_of(L" \n\r\t") + 1);
            currentString.erase(0, currentString.find_first_not_of(L" \n\r\t"));
            result << handleString(currentString);
        }

        while (!tests.eof()) {
            getline(tests, currentString);

            if (!currentString.empty()) {
                currentString.erase(currentString.find_last_not_of(L" \n\r\t") + 1);
                currentString.erase(0, currentString.find_first_not_of(L" \n\r\t"));
                if (iswdigit(currentString[0]))
                    result << endl;
                if (iswdigit(currentString[0]) ||
                    (currentString[0] == L'A' || currentString[0] == L'А' ||
                     currentString[0] == L'B' || currentString[0] == L'В' ||
                     currentString[0] == L'C' || currentString[0] == L'С' ||
                     currentString[0] == L'D' ||
                     currentString[0] == L'E' || currentString[0] == L'Е')) {
                    result << endl;
                    currentString = handleString(currentString);
                }
                result << currentString;
            }
        }
        result << endl;

        tests.close();
        result.close();

        wcout << L"  Файл " << fileName << L" считан. Результат записан в файл " <<
                 resultFileName.substr(resultFileName.find_last_of(L"/") + 1) <<
                 L" в директории results." << endl;
    }
    else
        wcout << L"  Не удалось открыть файл " << fileName << L" на чтение." << endl;
}

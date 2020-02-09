#include <cctype>

using namespace std;

wstring handleString(const wstring& value) {
    if (iswdigit(value[0])) {
        unsigned i = 0;
        while (iswdigit(value[i])) {
            i++;
        }
        if (value[i] == L' ' || value[i] == L'\t')
            i++;
        else if (value[i] == L'.' && (value[i + 1] == L' ' || value[i + 1] == L'\t'))
            i += 2;
        return L"?\n" + value.substr(i);
    }
    else if (value[0] == L'A' || value[0] == L'А') { //both russian and english letters should be accepted
        wstring buffer = L"+ " + value.substr(value.substr(1).find_first_not_of(L" .\t") + 1);
        if (buffer[buffer.length() - 1] == L'*')
            buffer.erase(buffer.length() - 1);
        return buffer;
    }
    else if (value[0] == L'B' || value[0] == L'В' ||
             value[0] == L'C' || value[0] == L'С' ||
             value[0] == L'D' ||
             value[0] == L'E' || value[0] == L'Е') {
        return L"- " + value.substr(value.substr(1).find_first_not_of(L" .\t") + 1);
    }
    return value;
}


wstring transformFileExtension(const wstring& value) {
    return value.substr(0, value.find_last_of(L".")) + L".qst";
}

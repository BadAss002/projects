int main() {
    char a = 'a';
    wchar_t wa = L'a';
    char e1 = '';
    wchar_t e2 = L'';
    int mc1 = 'ABCD';
    int mc2 = 'ABCDE';

    int mc3 = '/*';
    int mc4 = '//';

    char o1 = '\0';
    char o2 = '\007';
    char o3 = '\08';
    char o4 = '\009';
    char o5 = '\777';
    char o6 = '\4000';


    char h1 = '\xFF';
    char h2 = '\x';
    char h3 = '\xG'; 
    wchar_t h4 = L'\xt';

    char h5 = '\x1234567890ABCDEF123456';

    char h6 = '\x1\x2\x3\x4\x5';

    const char* str1 = " 'A' ";
    const char* str2 = " \"'\" ";
    const char* str3 = " \\' ";
    /* 'X' */
    // 'Y'
    /*
       'Z'
    */

    char q1 = '\'';
    char q2 = '\"';
    char q3 = '\\';
    char q4 = '\?';
    char q5 = '\q\q\q\q';
    return 0;
}

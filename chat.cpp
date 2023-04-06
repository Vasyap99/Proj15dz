#include "chat.h"
#include <iostream>
#include <string.h>

Chat::Chat() {
    count = 0;
    
    mem_size = 8;
    data = new AuthData[mem_size];    
}
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    /*AuthData a(_login,sha1(_pass, pass_length));
    memcpy((void*)&(data[count++]),(void*)&a,sizeof(AuthData));*/
    add( _login, sha1(_pass, pass_length) );
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    // Нужно вернуть true в случае успешного логина
    
    uint* h=sha1(_pass, pass_length);
    for(int i=0;i<mem_size;i++){
        if( data[i].status == enPairStatus::engaged &&/**/ strcmp(data[i].login,_login)==0 && memcmp(data[i].pass_sha1_hash,h,4*SHA1HASHLENGTHUINTS)==0) return true;
    }
    return false;
}


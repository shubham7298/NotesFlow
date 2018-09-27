string enc(string message, int key)
{
    key = key%256;
    char ch;
    int i;

    for(i = 0; message[i] != '\0'; ++i){
        ch = message[i];
        ch += key;
        message[i] = ch%256;

    }

    return message;
}


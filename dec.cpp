string dec(string message, int key)
{
    key = key%256;
    char ch;
    int i;

    for(i = 0; message[i] != '\0'; ++i){
        ch = message[i];
        if(ch-key < 0){
            ch = (ch + 256) - key;
        }
        else{
            ch -= key;
        }
        message[i] = ch;
    }

    return message;
}

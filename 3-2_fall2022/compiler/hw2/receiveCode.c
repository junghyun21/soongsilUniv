int num;
enum {NULL, NUMBER, PLUS, STAR, LP, RP, END} token;

void main()
{
    int result;
    get_token();
    result = expression();
    if(token != END) error(3);
    else printf("%d\n", result);
}

int expression()
{
    int result;
    result = term();
    while(token == PLUS)
    {
        get_token();
        result = result + term();
    }
    return result;
}

int term()
{
    int result;
    result = factor();
    while(token == STAR)
    {
        get_token();
        result = result * factor();
    }
    return result;
}

int factor()
{
    int result;
    if(token == NUMBER)
    {
        result = num;
        get_token();
    }
    else if(token == LP)
    {
        get_token();
        result = expression();
        if(token == RP) get_token();
        else error(2);
    }
    else error(1);
    return result;
}

void get_token()
{
    // next token --> token
    // number value --> num
}

void error(int i)
{
    switch(i)
    {
        case 1: //... break;
        case 2: //... break;
        case 3: //... break;
    }
    exit(1);
}
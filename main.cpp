#include <iostream>
#include <fstream>
#include <stdio.h>

inline int max(int a, int b){
    return (a > b)? a : b;
}

class Node{
private:
    int _x;
    Node* _nextNode;
    Node* _prevNode;
public:
    Node(int x){
        _x = x;
        _nextNode = NULL;
        _prevNode = NULL;
    }
    int x(){
        return _x;
    }
    void x(int x){
        _x = x;
    }
    Node* nextNode(){
        return _nextNode;
    }
    void nextNode(Node* node){
        _nextNode = node;
    }
    Node* prevNode(){
        return _prevNode;
    }
    void prevNode(Node* node){
        _prevNode = node;
    }

    int go(){
        std::cout << ">" << _x << std::endl;
        if( (_prevNode == NULL) || (_nextNode == NULL) ){
           return _x;
        }else{
            return _x + max( _prevNode->go(), _nextNode->go() );
        }
    }
};

int main(int argc, char** argv)
{
    std::string fileName("Triangle.in");
    if(argc > 1){
        fileName = argv[1];
    }

    FILE *f = fopen( fileName.data(), "rt" );

    int x, i = 0;
    int count = 15; // #FixMe : HardCode
    int currentLine = 1;
    int nextLine = 1;
    Node** tree = new Node*[count];
    for(int j=0; j<count; ++j){
        tree[j] = new Node(0);
    }
    // Пишем шапку таблицы
    std::cout << "i" << " : (x) | " << "currentLine" << std::endl;
    while( fscanf(f, "%i", &x) == 1 ){
        // Создаём узел в дереве
//        tree[i] = new Node(x);
        tree[i]->x(x);

        if( i == nextLine ){
            // Увеличиваем счётчик текущей строки
            currentLine++;
            // Прибавляем количество чисел в текущей строке
            // Которое по счастливой случайности равно номеру строки
            nextLine += currentLine;
        }

        if( (count - currentLine) > i ){
            std::cout << "+";
            tree[i]->prevNode( tree[i+currentLine] );
            tree[i]->nextNode( tree[i+currentLine+1] );
        }

        std::cout << i << " : (" << x << ") | " << currentLine << std::endl;

        ++i;
    }
    std::cout << "Result: " << tree[0]->go() << std::endl;

    fclose(f);

    /*
    std::fstream file;
    file.open(fileName.data(), std::ios::binary | std::ios::in | std::ios::out);

    char one[64];

    file.getline(one, sizeof(one));
    std::cout << one << std::endl;

    file.close();
    */

    return 0;
}


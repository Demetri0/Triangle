#include <iostream>
#include <stdio.h>

inline int max(int a, int b){
    return (a > b)? a : b;
}
inline int countNum(const char* fileName){
    FILE *f = fopen( fileName, "rt" );
    int i = 0, x;
    while( fscanf(f, "%i", &x) == 1 ){++i;}
    fclose(f);
    return i;
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
        if( (_prevNode == NULL) || (_nextNode == NULL) ){
           return _x;
        }else{
            return _x + max( _prevNode->go(), _nextNode->go() );
        }
    }
};

int main(int argc, char** argv)
{
    char* fileIn = "Triangle.in";
    char* fileOut = "Triangle.out";
    if(argc > 1){
        fileIn = argv[1];
        if(argc > 2)
            fileOut = argv[2];
    }

    FILE *f = fopen( fileIn, "rt" );

    int x, i = 0;
    int count = countNum( fileIn );
    int currentLine = 1;
    int nextLine = 1;

    // Создаём дерево
    Node** tree = new Node*[count];
    for(int j=0; j<count; ++j){
        tree[j] = new Node(0);
    }

    // Пишем шапку таблицы
    while( fscanf(f, "%i", &x) == 1 ){
        // Создаём узел в дереве
        // tree[i] = new Node(x);

        // Инициализируем значение узла
        tree[i]->x(x);

        if( i == nextLine ){
            // Увеличиваем счётчик текущей строки
            currentLine++;
            // Прибавляем количество чисел в текущей строке
            // Которое по счастливой случайности равно номеру строки
            nextLine += currentLine;
        }

        if( (count - currentLine) > i ){
            tree[i]->prevNode( tree[i+currentLine] );
            tree[i]->nextNode( tree[i+currentLine+1] );
        }

        ++i;
    }
    fclose(f);

    // Вычисляем!
    int result = tree[0]->go();
    std::cout << "Result: " << result << std::endl;

    // Пишем в файл
    f = fopen( fileOut, "wt" );
    fprintf(f,"%i",result);
    fclose(f);

    return 0;
}


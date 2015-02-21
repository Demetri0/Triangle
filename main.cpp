#include <stdio.h>

// Максимально число из двух
inline int max(int a, int b){
    return (a > b)? a : b;
}

// Подсчёт кол-ва чисел в файле
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
    // Конструктор с очень важной инициализацией
    Node(int x){
        _x = x;
        _nextNode = NULL;
        _prevNode = NULL;
    }

    // Бесполезная мешура
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
        // Если нет связанных узлов возвращаем значение текущего узла
        if( (_prevNode == NULL) || (_nextNode == NULL) ){
           return _x;
        }else{
            // Значение текущего узла + максимальное из связанных узлов
            return _x + max( _prevNode->go(), _nextNode->go() );
        }
    }
};

int main(int argc, char** argv)
{
    char* fileIn = "Triangle.in";
    char* fileOut = "Triangle.out";

    // Если есть параметры считаем первый
    // именеи входного файла
    if(argc > 1){
        fileIn = argv[1];
        // Если есть второй аргумент - считаем его именем
        // выходного файла
        if(argc > 2)
            fileOut = argv[2];
    }

    // Получаемое значение и текущая итерация
    int x, i = 0;
    // Кол-во чисел в файле
    int count = countNum( fileIn );
    // Изначальные строка и конец строки
    int currentLine = 1;
    int nextLine = 1;

    // Создаём дерево
    Node** tree = new Node*[count];
    for(int j=0; j<count; ++j){
        tree[j] = new Node(0);
    }

    FILE *f = fopen( fileIn, "rt" );
    if(f == 0){
        printf("Error! File '%s' is not exists.\n", fileIn);
        return 1;
    }

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

        // Создаём связи
        if( (count - currentLine) > i ){
            tree[i]->prevNode( tree[i+currentLine] );
            tree[i]->nextNode( tree[i+currentLine+1] );
        }

        ++i;
    }
    fclose(f);

    // Вычисляем!
    int result = tree[0]->go();
    printf("Result: %i\n", result);

    // Пишем в файл
    f = fopen( fileOut, "wt" );
    fprintf(f,"%i",result);
    fclose(f);

    return 0;
}


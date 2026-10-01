#include <iostream>
#include <SFML/Graphics.hpp>
#include "RB_TREE.h"
using namespace std;

float dimX = 1000, dimY = 1000;
float nodeSize = 50;
sf::Font font;
sf::Text text;
sf::RenderWindow win(sf::VideoMode(dimX, dimY), "Tree");
sf::RectangleShape square(sf::Vector2f(nodeSize, nodeSize));
auto red = sf::Color(255, 0, 0), blk = sf::Color(0, 0, 0);

void init() {
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(nodeSize/2.5);
    text.setFillColor(sf::Color::White);
    square.setOrigin(nodeSize/2, nodeSize/2);
}

void draw_line(float x1, float y1, float x2, float y2)   {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(x1, y1), blk),
        sf::Vertex(sf::Vector2f(x2, y2), blk)
    };
    win.draw(line, 2, sf::Lines);
}

void plot_node(const Node* node, float x, float y)  {
    if (node && node->red)
        square.setFillColor(red);
    else
        square.setFillColor(blk);
    square.setPosition(x, y);
    win.draw(square);
    text.setString((node ? to_string(node->val) : "null"));
    sf::FloatRect f;
    f = text.getLocalBounds();
    text.setOrigin((f.top+f.height)/2, (f.left+f.width)/2);
    text.setPosition(x, y);
    win.draw(text);
}

// current node, current pos
void make_tree(const Node* root, float x, float y, float gap)  {
    if (!root)
        return;
    // draw lines first
    if (root->left)  {
        draw_line(x, y, x - gap/2, y+100);
        make_tree(root->left, x - gap/2, y+100, gap/2);
    }
    if (root->right)    {
        draw_line(x, y, x + gap/2, y+100);
        make_tree(root->right, x + gap/2, y+100, gap/2);
    }
    plot_node(root, x, y);
}

void save_tree(const Node* root)    {
    static int img_no = 1;
    if (!root)
        return;
    win.clear(sf::Color::White);
    // traverse and make the image, inorder
    draw_line(dimX/2, 50, dimX/2 - dimX/4, 50+100);
    draw_line(dimX/2, 50, dimX/2 + dimX/4, 50+100);
    plot_node(root, dimX/2, 50);
    make_tree(root->left, dimX/2 - dimX/4, 50+100, dimX/4);
    make_tree(root->right, dimX/2 + dimX/4, 50+100, dimX/4);
    sf::Image img = win.capture();
    string name = "imgs/tree" + to_string(img_no++);
    name += ".png";
    img.saveToFile(name);
    win.display();
}

bool evaluate(string &s, rb_tree &t)    {
    char c = s.back();
    s.pop_back();

    if (c == 'e')
        return 1;

    // check for invalid arguments
    int st = s[0] == '-';
    for (; st < s.size(); ++st)
        if (!isdigit(s[st])) {
            cout << "Invalid operation";
            return 0;
        }

    int v = stoi(s);
    
    bool f;
    switch(c)   {
        case 'i':
        t.insert(v);
        cout << "Inserted " << v;
        break;
        case 'd':
        t.erase(v);
        cout << "Deleted " << v;
        break;
        case 'f':
        f = t.find(v);
        if (f)  cout << "Found " << v;
        else    cout << v << " not found";
        break;
        default:
        cout << "Invalid operation";
        return 0;
    }
    if (c != 'f')
        save_tree(t.__GET_ROOT__());
    return 0;
}

int main()  {
    rb_tree t;
    init();
    const Node* root = nullptr;
    cout << "Insert: {num}i | Example: 5i // inserts 5";
    cout << "\nDelete: {num}d | Example: 5d // deletes 5";
    cout << "\nFind: {num}f | Example: 5f // finds 5";
    cout << "\nExit: e";
    string s;

    while (win.isOpen())   {
        cout << "\n\nChoice: ";
        cin >> s;
        bool ex = evaluate(s, t);
        if (ex) win.close();
        sf::Event event;
        while (win.pollEvent(event))
            if (event.type == sf::Event::Closed)
                win.close();
    }    

    return 0;
}

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  setlocale(LC_ALL, "RUS");

  ifstream f;
  f.open("example.txt");
  if (f.is_open())
  {
    int x;
    while (!f.eof())
    {
      f >> x;
      if (!f.fail())
      {
        cout << x << " ";
      }
      else
      {
        cout << "x"
             << " ";
        if (!f.eof())
        {
          f.clear();
          f.seekg(1, ios_base::cur);
        }
      }
    }
    f.close();
  }
  else
  {
    cout << "Файл не открылся" << endl;
  }
  return 0;
}

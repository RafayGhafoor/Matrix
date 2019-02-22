#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

class Set
{
  private:
    int size, *sptr;

  public:
    Set(int s)
    {
        size = s;
        sptr = new int[s];
    }

    Set(Set &obj)
    {
        size = obj.size;
        sptr = new int[size];
        for (int i = 0; i < obj.size; i++)
            sptr[i] = obj.sptr[i];
    }

    ~Set()
    {
        if (sptr != nullptr)
        {
            delete[] sptr;
            sptr = nullptr;
        }
    }

    void print()
    {
        if (sptr != nullptr)
        {
            for (int i = 0; i < size; i++)
                cout << sptr[i] << " ";
        }
    }

    void removeRepetition()
    {
        int track_repeats = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (i != j && sptr[i] == sptr[j])
                {
                    track_repeats++;
                    for (int t = i; t + 1 < size; t++)
                        while (sptr[t] == sptr[t + 1] && t + 1 < size) // 1 2 2 2 2 3
                            sptr[t] = sptr[t + 1];
                }
            }
        }
        size -= track_repeats;
    }

    Set Difference(Set &obj)
    {
        Set ans(*this);
        for (int i = 0; i < size; i++)
            ans.sptr[i] -= obj.sptr[i];
        return ans;
    }

    Set Union(Set &obj)
    {
        removeRepetition();
        obj.removeRepetition();
        ans(obj);
        ans.size = obj.size + size;

        for (int index = obj.size, i = 0; i < obj.size + size; i++)
            ans.sptr[index++] = sptr[i];

        return ans;
    }

    Set Intersection(Set &obj)
    {
        int track_common = 0;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (i != j && sptr[i] == obj.sptr[j])
                    track_common++;

        Set ans(track_common);

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (i != j && sptr[i] == obj.sptr[j])
                    ans.ptr[i] = sptr[j];

        return ans;
    }

    Set PowerSet()
    {
        Set ans(*this);
        int k = 0;

        ans.sptr[0] = 0; /* 0 is not considered as part of the set */

        while (1)
        {
            if (ans.sptr[k] < ans.size)
            {
                ans.sptr[k + 1] = ans.sptr[k] + ans.sptr[k + 1];
                k++;
            }
            else
            {
                ans.sptr[k - 1]++;
                k--;
            }

            if (k == 0)
                break;
        }
    }
    return ans;
}
}
;

void Menu()
{
    // TODO
    cout << R"(
    01- Allocate Member Array.
    02- Make a Copy.
    03- Call the Destructor.
    04- Print Set.
    05- Remove Repetition.
    06- Read from file.
    07- Show Union between two sets.
    08- Show Intersection between two sets.
    09- Show Set Difference between two sets.
    10- Get Power Set of the Array.)";

    char input;
    cout << "Please enter your choice: ";

    while (cin >> input)
    {

        else if (input == '0')
        {
        }
        else if (input == '1')
        {
        }
        else if (input == '2')
        {
        }
        else if (input == '3')
        {
        }
        else if (input == '4')
        {
        }
        else if (input == '5')
        {
        }
        else if (input == '6')
        {
        }
        else if (input == '7')
        {
        }
        else if (input == '8')
        {
        }
        else if (input == '9')
        {
        }
        else cout << "Invalid input specified" << endl;
    }
}
int main() {}
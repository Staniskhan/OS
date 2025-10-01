#include <iostream>
#include <thread>
#include <chrono>

struct min_max_struct {
    int* arr;
    int size;
    int min;
    int max;
};

struct avg_struct {
    int* arr;
    int size;
    int avg;
};

void min_max(min_max_struct* ret_struct) {
    ret_struct->min = ret_struct->arr[0];
    ret_struct->max = ret_struct->arr[0];
    for (int i = 0; i < ret_struct->size; i++) {
        if (ret_struct->min > ret_struct->arr[i]) {
            ret_struct->min = ret_struct->arr[i];
            std::this_thread::sleep_for(std::chrono::milliseconds(7));
        }
        else if (ret_struct->max < ret_struct->arr[i]) {
            ret_struct->max = ret_struct->arr[i];
            std::this_thread::sleep_for(std::chrono::milliseconds(7));
        }
    }
}

void average(avg_struct* ret_struct) {
    ret_struct->avg = 0;
    for (int i = 0; i < ret_struct->size; i++) {
        ret_struct->avg += ret_struct->arr[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(12));
    }
    if (((10 * ret_struct->avg) / ret_struct->size) % 10 >= 5) {
        ret_struct->avg = ret_struct->avg / ret_struct->size + 1;
    }
    else {
        ret_struct->avg /= ret_struct->size;
    }
}

int main() {
    int n;
    std::cout << "Enter the size of array: ";
    std::cin >> n;
    int* arr = new int[n];
    std::cout << "Enter the elements of array separating them with whitespace or each on a new line:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    min_max_struct mms;
    mms.arr = arr;
    mms.size = n;

    avg_struct as;
    as.arr = arr;
    as.size = n;

    std::thread minMaxThread(min_max, &mms);
    std::thread avgThread(average, &as);

    minMaxThread.join();
    avgThread.join();

    std::cout << "min: " << mms.min
              << "\nmax: " << mms.max
              << "\navg: " << as.avg;

    for (int i = 0; i < n; i++) {
        if (arr[i] == mms.min || arr[i] == mms.max) {
            arr[i] = as.avg;
        }
    }

    std::cout << "\n\nThe processed array:\n";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n\n";

    system("pause");
    return 0;
}
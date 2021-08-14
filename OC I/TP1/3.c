void insertionSort(int arr[], int n) {
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

int main() {
  int arr[] = {27, 16, 20, 49, 39, 48, 38, 7, 5, 19};
  int n = sizeof(arr) / sizeof(arr[0]);
  insertionSort(arr, n);
  return 0;
}
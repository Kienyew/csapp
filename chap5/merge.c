
void merge(int arr1[], int arr2[], int dest[], int n) {
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < n && j < n) {
		int min = (arr1[i] < arr2[j]) ? arr1[i++] : arr2[j++];
		dest[k++] = min;
	}

	while (i < n) {
		dest[k++] = arr1[i++];
	}

	while (j < n) {
		dest[k++] = arr1[j++];
	}
}

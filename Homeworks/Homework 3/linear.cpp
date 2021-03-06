// Return true if the somePredicate function returns false for at
// least one of the array elements; return false otherwise.
bool anyFalse(const double a[], int n) {
	if (n <= 0 ) {
		return false;
	}
	if (somePredicate(a[0]) == false) {
		return true;
	}

	return anyFalse(a + 1, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n) {
	if (n <= 0) {
		return 0;
	}
	int count = countTrue(a + 1, n - 1);
	if (somePredicate(a[0]) == false) {
		return count + 1;
	}
	return count;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n) {
	if (n <= 0) {
		return -1;
	}
	if (somePredicate(a[0]) == true) {
		return 0;
	}
	else {
		int f = firstTrue(a + 1, n - 1);
		if (f == -1) {
			return f;
		}
		return f + 1;
	}
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int positionOfSmallest(const double a[], int n) {
	if (n <= 0) {
		return -1;
	}
	if (n == 1) {
		return 0;
	}
	if (a[0] < a[positionOfSmallest(a + 1, n - 1) + 1]) {
		return 0;
	}
	else
		return positionOfSmallest(a + 1, n - 1) + 1;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
	 // the same order (though not necessarily consecutively), then
	 // return true; otherwise (i.e., if the array a1 does not contain
	 // a2 as a not-necessarily-contiguous subsequence), return false.
	 // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
	 // For example, if a1 is the 7 element array
	 //    10 50 40 20 50 40 30
	 // then the function should return true if a2 is
	 //    50 20 30
	 // or
	 //    50 40 40
	 // and it should return false if a2 is
	 //    50 30 20
	 // or
	 //    10 20 20
bool contains(const double a1[], int n1, const double a2[], int n2) {
	if (n2 < 0) {
		return false;
	}
	if (n1 == 0 && n2 != 0) {
		return false;
	}
	if (n2 == 0) {
		return true;
	}
	if (a1[0] == a2[0]) {
		return contains(a1, n1, a2 + 1, n2 - 1);
	}
	else {
		return contains(a1 + 1, n1 - 1, a2, n2);
	}
}
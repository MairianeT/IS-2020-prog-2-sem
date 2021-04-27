#ifndef PREDICATE_HPP 
#define PREDICATE_HPP


template <class InputIterator, class UnaryPredicate>
bool allOf(InputIterator begin, InputIterator end, const UnaryPredicate& function) {
	for (; begin != end; ++begin) {
		if (!function(*begin)) {
			return false;
		}
	}

	return true;
};

template <class InputIterator, class UnaryPredicate>
bool anyOf(InputIterator begin, InputIterator end, const UnaryPredicate& function) {
	for (; begin != end; ++begin) {
		if (function(*begin)) {
			return true;
		}
	}

	return false;
};

template <class InputIterator, class UnaryPredicate>
bool noneOf(InputIterator begin, InputIterator end, const UnaryPredicate& function) {
	return !anyOf(begin, end, function);
};

template <class InputIterator, class UnaryPredicate>
bool oneOf(InputIterator begin, InputIterator end, const UnaryPredicate& function) {
	int count = 0;

	for (; begin != end; ++begin) {
		if (function(*begin)) {
			count++;
		}
	}

	if (count == 1) {
		return true;
	}
	else {
		return false;
	}
};

template <class InputIterator, class BinaryPredicate = std::less<>>
bool isSorted(InputIterator begin, InputIterator end, const  BinaryPredicate function = BinaryPredicate() ) {
	for (; begin != end - 1; ++begin) {
		if (!function(*begin, *(begin + 1))) {
			return false;
		}
	}

	return true;
};

template <class InputIterator, class UnaryPredicate>
bool isPartitioned(InputIterator begin, InputIterator end, const UnaryPredicate& function) {

	int fl = 0;
	for (; begin != end - 1; ++begin) {
		if (function(*begin) != function(*(begin + 1))) {
			if (fl == 0) {
				fl = 1;
			}
			else
				return false;
		}
	}

	if (fl == 1)
		return true;
	else
		return false;

};

template <class InputIterator, class T>
InputIterator findNot(InputIterator begin, InputIterator end, const T& value) {
	for (; begin != end; ++begin) {
		if (*begin != value) {
			return begin;
		}
	}

	return end;
};

template <class ForwardIterator, class T>
ForwardIterator findBackward(ForwardIterator begin, ForwardIterator end, const T& value) {
	ForwardIterator result = end;

	for (; begin != end; ++begin) {
		if (*begin == value) {
			result = begin;
		}
	}

	return result;
};

template <class BidirectionalIterator, class BinaryPredicate>
bool isPalindrome(BidirectionalIterator begin, BidirectionalIterator end, const BinaryPredicate& function) {
	--end;
	while (begin != end) {
		if (!function(*begin, *end)) {
			return false;
		}
		++begin;
		if (begin != end)
		--end;
	}
	return true;
};

#endif
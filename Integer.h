// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h   

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <math.h> 
#include <algorithm> 

using namespace std;
// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 */
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {
    while (b != e) {
        *x = *b;
    	++x;
    	++b; }
    while (n) {
        *x = 0;
        ++x;
        --n; }
    return x;}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
/*
 void test_shift_right_digits () {
 const int a[] = {2, 3, 4};
 const int b[] = {2};
 int x[10];
 const int* p = shift_right_digits(a, a + 3, 2, x);
 CPPUNIT_ASSERT((p - x) == 1);
 CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}
 */
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
    vector<int> vec1;
	while(b != e) {
        vec1.push_back(*b);
        ++b;
	}
    int vec1Len = vec1.size();
    int temp = vec1Len - n;
    int i = 0;
    while(temp) {
        *x = vec1[i];
        ++x; ++i; --temp;
    }
    return x;}

// -----------
// plus_digits
// -----------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	vector<int> vec1;
	vector<int> vec2;
	while (b1 != e1) {
	    vec1.push_back(*b1);
	    ++b1; }
	while (b2 != e2) {
		vec2.push_back(*b2);
	    ++b2; }
	int vec1Len = vec1.size();
	int vec2Len = vec2.size();
	
	vector<int> vec3;
	int i = 0;
	int j = 0;
	if(vec1Len != vec2Len) {
		if(vec1Len > vec2Len) {
			int lenDiff = vec1Len - vec2Len;
			while (lenDiff) {
				vec3.push_back(vec1.at(i));
				++i; --lenDiff;}
			while(vec2Len) {
				vec3.push_back((vec1.at(i) + vec2.at(j)));
				--vec2Len; ++i; ++j; }
		}
		else {
			int lenDiff = vec2Len - vec1Len;
			while (lenDiff) {
				vec3.push_back(vec2.at(i));
				++i; --lenDiff;}
			while(vec1Len) {
				vec3.push_back(vec2.at(i) + vec1.at(j));
				--vec1Len; ++i; ++j;}
		}
	}
	else {
		while(vec1Len) {
			vec3.push_back(vec1.at(i) + vec2.at(j));
			++i;++j;
			--vec1Len; }
	}
	vector<int>::reverse_iterator iter;
	vector<int> temp;
	bool add = false;
	for(iter = vec3.rbegin(); iter != vec3.rend(); ++iter) {
		if(add) {
			*iter += 1;
			add = false;}
		if(*iter >= 10) {
			*iter = *iter - 10;
			add = true;}
		temp.push_back(*iter);
	}
	for (vector<int>::reverse_iterator it = temp.rbegin(); it != temp.rend(); ++it) {
		*x = *it;
		++x;
	}
    return x;}

// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	vector<int> vec1;
	vector<int> vec2;
	while (b1 != e1) {
	    vec1.push_back(*b1);
	    ++b1;}
	while (b2 != e2) {
		vec2.push_back(*b2);
	    ++b2;}
	int vec1Len = vec1.size();
	int vec2Len = vec2.size();
    
	if(vec1Len < vec2Len) {
	    *x = -1;
 	    ++x;
	    return x;}
	else if (vec1Len == vec2Len) {
	    int vec1Num = 0; int vec2Num = 0;
	    for (int i = 0; i < vec1Len; i++) {
            vec1Num += vec1[i] * pow(10, (vec1Len-i-1)); }
	    for (int j = 0; j < vec2Len; j++) {
            vec2Num += vec2[j] * pow(10, (vec1Len-j-1)); }
	    if(vec1Num < vec2Num) {
	        *x = -1;
	        ++x;
	        return x;}
	    else if(vec1Num == vec2Num) {
		    *x = 0;
		    ++x;
            return x;}
	}
    int lenDiff = vec1Len - vec2Len;
    int borrow = 0;
    vector<int> vec3;
    int i = vec1Len-1; int j = vec2Len-1;
    while(vec2Len) {
        int temp = vec1.at(i) - vec2.at(j) - borrow;
        if(temp < 0) {
            temp += 10;
            borrow = 1;}
        else
            borrow = 0;
        vec3.push_back(temp);
        --vec2Len;
        --i;
        --j;
    }
    vec2Len = vec2.size();
    if(vec1Len > vec2Len) {
        while(lenDiff) {
            int temp = vec1.at(i) - borrow;
            if(temp < 0) {
                temp += 10;
                borrow = 1;}
            else
                borrow = 0;
            if(temp != 0)
                vec3.push_back(temp);
            --i;
            --lenDiff;}
    }
    for (vector<int>::reverse_iterator it = vec3.rbegin() ; it != vec3.rend(); ++it) {
        *x = *it;
        ++x;}
    return x;}


// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    vector<int> vec1;
	vector<int> vec2;
	while (b1 != e1) {
	    vec1.push_back(*b1);
	    ++b1;}
	while (b2 != e2) {
		vec2.push_back(*b2);
	    ++b2;}
	vector<int> vec3 ((vec1.size()+vec2.size()), 0);
	int vec3Len = vec3.size();
	int count = 0 ;
	int carry2 = 0;
	for (vector<int>::reverse_iterator v2 = vec2.rbegin() ; v2 != vec2.rend(); ++v2) {
		int temp = 0;
		int carry = 0;
		int j = 1;
		for (vector<int>::reverse_iterator v1 = vec1.rbegin() ; v1 != vec1.rend(); ++v1) {
			temp = *v2 * *v1 + carry;
			if(temp >= 10) {
				carry = temp / 10;
				temp = temp % 10;}
			else
				carry = 0;
			temp  = temp + vec3[vec3Len-j-count] + carry2;
			if (temp >= 10) {
				carry2 = temp/10;
				temp %= 10; }
			else
				carry2 = 0;
			vec3[vec3Len-j-count] = temp;
			++j;
		}
		if(carry) {
			temp = carry;
            if(temp > 9) {
                int temp2 = temp/10;
                temp %= 10;
                vec3[vec3Len-j-count] = temp;
                vec3[vec3Len-j-count-1] = temp2;
            }
            else
			    vec3[vec3Len-j-count] = temp; }
		++count;
	}
	bool first = true;
	for (vector<int>::iterator it = vec3.begin() ; it != vec3.end(); ++it) {
        if(first && *it == 0) {
            first = false;
        }
        else {
		   *x = *it;
           ++x;
        }
        first = false;
	}
	
    return x;}

// --------------
// divides_digitsx
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    
    vector<int> vec1;
    vector<int> vec2;
    while (b1 != e1) {
        vec1.push_back(*b1);
        ++b1;}
    while (b2 != e2) {
        vec2.push_back(*b2);
        ++b2;}
    
    int vec1Len = vec1.size();  int vec2Len = vec2.size();
    int lenDiff = vec1Len - vec2Len;
    int shiftedLen = vec2Len + lenDiff;
    
    vector<int>::iterator v1itb = vec1.begin();
    vector<int>::iterator v1ite = vec1.end();
    
    vector<int>::iterator v2itb = vec2.begin();
    vector<int>::iterator v2ite = vec2.end();
    
    deque<int> shifted;
    shifted.resize(shiftedLen);
    deque<int>::iterator shiftedb = shifted.begin();
    deque<int>::iterator shiftede = shifted.end();
    shift_left_digits(v2itb, v2ite, lenDiff, shiftedb);
    
    deque<int> result;
    result.resize(vec1Len);
    deque<int>::iterator resultb = result.begin();
    
    
    vector<int> quotient;
    bool go = true;
    int resultLen = 0;
    deque<int>::iterator p;
    int temp = 0;
    int count = 0;
    bool first = true;
    while(go) {
        if(first)
            p = minus_digits(v1itb, v1ite, shiftedb, shiftede, resultb);
        else {
	        temp = *resultb;
	        p = minus_digits(resultb, resultb + resultLen, shiftedb, shiftede, resultb); }
        
        if(*resultb == -1) {
            shift_right_digits(shiftedb, shiftede, 1, shiftedb);
            *resultb = temp;
            --shiftede;
            if(count !=0) {
                quotient.push_back(count);
                count = 0;}
        }
        else if(result[0] == 0) {
            ++count;
            quotient.push_back(count);
            go = false;}
        else {
            first = false;
            ++count;
            resultLen = (p - resultb);
        }
    }
    bool notBeenFirstIf = true;
    if(lenDiff > 0 && count == 1) {
        notBeenFirstIf = false;
        count = lenDiff * 10;
        bool first = true;
        int countLen = log10((float)count) + 1;
        for(int i = countLen-1; i>=0; i--) {
            int divisor = pow((float)10, i);
            int digit = count/divisor;
            if(!first)
                quotient.push_back(digit);
            count -= digit * divisor;
            first = false;
        }
    }
    int quoVec2 = quotient.size() + vec2Len;
    if((quoVec2 != vec1Len) & notBeenFirstIf) {
        int num = vec1Len-(quotient.size() + vec2Len);
        while(num) {
            quotient.push_back(0);
            --num;
        }
    }
    for(vector<int>::iterator it = quotient.begin() ; it != quotient.end(); ++it) {
        *x = *it;
        ++x;
    }
    return x;}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------
    
    /**
     * <your documentation>
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        if(lhs.sign != rhs.sign) 
            return false;
        if(lhs.vec.size() != rhs.vec.size()) 
            return false;
        for(unsigned int i = 0; i<lhs.vec.size(); i++) {
            if(lhs.vec[i] != rhs.vec[i]) {
                return false;
	    }
        }
        return true;}
    
    // -----------
    // operator !=
    // -----------
    
    /**
     * <your documentation>
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);}
    
    // ----------
    // operator <
    // ----------
    
    /**
     * <your documentation>
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        // <your code>
        if(lhs.sign == true && rhs.sign == false)
            return false;
        else if(lhs.sign ==false && rhs.sign == true)
            return true;
        else if(!lhs.sign  && !rhs.sign) {
            if(lhs.vec.size() < rhs.vec.size())
                return false;
            else if(lhs.vec.size()==rhs.vec.size()) {
                for(unsigned int i =0; i<lhs.vec.size(); i++) {
                    if(lhs[i] < rhs[i])
                        return false;
                }
            }
        }
        else{
            if(lhs.vec.size()< rhs.vec.size())
                return true;
            else if(lhs.vec.size()==rhs.vec.size()) {
                for(unsigned int i =0; i<lhs.vec.size(); i++) {
                    if(lhs[i] < rhs[i])
                        return true;
                }
            }
        }
        return false;
    }
    
    // -----------
    // operator <=
    // -----------
    
    /**
     * <your documentation>
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}
    
    // ----------
    // operator >
    // ----------
    
    /**
     * <your documentation>
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}
    
    // -----------
    // operator >=
    // -----------
    
    /**
     * <your documentation>
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}
    
    // ----------
    // operator +
    // ----------
    
    /**
     * <your documentation>
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}
    
    // ----------
    // operator -
    // ----------
    
    /**
     * <your documentation>
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}
    
    // ----------
    // operator *
    // ----------
    
    /**
     * <your documentation>
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}
    
    // ----------
    // operator /
    // ----------
    
    /**
     * <your documentation>
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}
    
    // ----------
    // operator %
    // ----------
    
    /**
     * <your documentation>
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}
    
    // -----------
    // operator <<
    // -----------
    
    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}
        
        // -----------
        // operator >>
        // -----------
        
        /**
         * <your documentation>
         * @throws invalid_argument if (rhs < 0)
         */
        friend Integer operator >> (Integer lhs, int rhs) {
            return lhs >>= rhs;}
        
        // -----------
        // operator <<
        // -----------
        
        /**
         * <your documentation>
         */
        friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
            // <your code>
                for(unsigned int i = 0; i<rhs.vec.size(); i++) {
                    lhs << rhs.vec[i];
                }
                return lhs;}
                
                // ---
                // abs
                // ---
                
                /**
                 * absolute value
                 * does NOT modify the argument
                 * <your documentation>
                 */
                friend Integer abs (Integer x) {
                    return x.abs();}
                
                // ---
                // pow
                // ---
                
                /**
                 * power
                 * does NOT modify the argument
                 * <your documentation>
                 * @throws invalid_argument if (x == 0) && (e == 0)
                 * @throws invalid_argument if (e < 0)
                 */
                friend Integer pow (Integer x, int e) {
                    return x.pow(e);}
                
            private:
                // ----
                // data
                // ----
                C vec;
                bool sign; //true means >0 and false means <0
                // <your data>
                
            private:
                // -----
                // valid
                // -----
                
                bool valid () const { /*
                    if(vec.size() == 0) {
                        cout<<"vec.size() == 0" << endl;
                        return false;
                    }*/
                    for(unsigned int i = 0; i < vec.size(); i++) {
                        if(vec[i]<0 || vec[i]>9 ){
                            return false;}
                    }
                    return true;}
                
            public:
                // ------------
                // constructors
                // ------------
                
                /**
                 * <your documentation>
                 */
                Integer (int value) {
                    if(value < 0) {
                        sign = false;
                        value *= -1;
                    }
                    else
                        sign = true;
                    assert(value>=0);
                    int vecSize = log10(value) + 1;
                    while(vecSize) {
                        int digit = value%10;
                        vec.insert(vec.begin(), digit);
                        value/=10;
                        --vecSize;
                    }
                    assert(valid());}

                int powerHelper(int a, int b) {
                        if(b == 0)
                            return 1;
                        int c=a;
                        for (int n=b; n>1; n--) c*=a;
                        return c;
                }
                /**
                 * <your documentation>
                 * @throws invalid_argument if value is not a valid representation of an Integer
                 */
                explicit Integer (const std::string& value) {
                    for(unsigned int i = 0 ; i < value.length(); i++) {
                        int num = value[i] - '0';
                        vec.push_back(num);
                    }
                    if (!valid())
                        throw std::invalid_argument("Integer::Integer()");}
                
                // Default copy, destructor, and copy assignment.
                // Integer (const Integer&);
                // ~Integer ();
                // Integer& operator = (const Integer&);
                
                // ----------
                // operator -
                // ----------
                
                /**
                 * <your documentation>
                 */
                Integer operator - () const {
                    Integer x = *this;
                    x.sign = !x.sign;
                    return x;}
                
                // -----------
                // operator ++
                // -----------
                
                /**
                 * <your documentation>
                 */
                Integer& operator ++ () {
                    *this += 1;
                    return *this;}
                
                /**
                 * <your documentation>
                 */
                Integer operator ++ (int) {
                    Integer x = *this;
                    ++(*this);
                    return x;}
                
                // -----------
                // operator --
                // -----------
                
                /**
                 * <your documentation>
                 */
                Integer& operator -- () {
                    *this -= 1;
                    return *this;}
                
                /**
                 * <your documentation>
                 */
                Integer operator -- (int) {
                    Integer x = *this;
                    --(*this);
                    return x;}
                
                // -----------
                // operator +=
                // -----------
                
                /**
                 * <your documentation>
                 */
                Integer& operator += (const Integer& rhs) {
                    C result;
                    plus_digits(rhs.vec.begin(), rhs.vec.end(), vec.begin(), vec.end(), result.begin());
                    vec = result;
                    return *this;}
                
                // -----------
                // operator -=
                // -----------
                
                /**
                 * <your documentation>
                 */
                Integer& operator -= (const Integer& rhs) {
                    C result;
                    minus_digits (vec.begin(), vec.end(), rhs.vec.begin(), rhs.vec.end(), result.begin());
                    vec = result;
                    return *this;}
                
                // -----------
                // operator *=
                // -----------
                
                /**
                 * <your documentation>
                 */
                Integer& operator *= (const Integer& rhs) {
                    C result;
                    multiplies_digits(vec.begin(), vec.end(), rhs.vec.begin(), rhs.vec.end(), result.begin());
                    vec = result;
                    return *this;}
                
                // -----------
                // operator /=
                // -----------
                
                /**
                 * <your documentation>
                 * @throws invalid_argument if (rhs == 0)
                 */
                Integer& operator /= (const Integer& rhs) {
                    if (!valid())
                        throw std::invalid_argument("Integer& operator /= invalid argument");
                    divides_digits(vec.begin(), vec.end(), rhs.vec.begin(), rhs.vec.end(), vec.begin());
                    return *this;}
                
                // -----------
                // operator %=
                // -----------
                
                /**
                 * <your documentation>
                 * @throws invalid_argument if (rhs <= 0)
                 */
                Integer& operator %= (const Integer& rhs) {
                    if (!valid())
                        throw std::invalid_argument("Integer& operator %= invalid argument");
                    C result;
                    divides_digits(vec.begin(), vec.end(), rhs.vec.begin(), rhs.vec.end(), result.begin());
                    multiplies_digits(result.begin(), result.end(), rhs.vec.begin(), rhs.vec.end(), result.begin());
                    minus_digits (vec.begin(), vec.end(), result.begin(), result.end(), vec.begin());
                    return *this;}
                
                // ------------
                // operator <<=
                // ------------
                
                /**
                 * <your documentation>
                 */
                Integer& operator <<= (int n) {
                    shift_left_digits (vec.begin(), vec.end(), n, vec.begin());
                    return *this;}
                
                // ------------
                // operator >>=
                // ------------
                
                /**
                 * <your documentation>
                 */
                Integer& operator >>= (int n) {
                    right_left_digits (vec.begin(), vec.end(), n, vec.begin());
                    return *this;}
                
                // ---
                // abs
                // ---
                
                /**
                 * absolute value
                 * <your documentation>
                 */
                Integer& abs () {
                    sign = true;
                    return *this;}
                
                // ---
                // pow
                // ---
                
                /**
                 * power
                 * <your documentation>
                 * @throws invalid_argument if (this == 0) && (e == 0)
                 * @throws invalid_argument if (e < 0)
                 */
                    Integer& pow (int e) {
                        if (!valid())
                            throw std::invalid_argument("Integer& operator /= invalid argument");
                        if(e == 0) {
                            return *this;
                        }
                        int vecInt = 0;
                        int vecLen = vec.size()-1;
                        for(int i=0; i<=vecLen; i++) {
                            vecInt += vec[i] * powerHelper(10, vecLen-i);
                        }
                        int result = 1;
                        while(e) {
                            result *= vecInt;
                            --e;
                        }
                        while (!vec.empty()) {
                            vec.pop_back();
                        }
                        int resultLen = log10(result);
                        for(int i = resultLen; i >= 0; i--) {
                            int divisor = powerHelper(10, i);
                            int digit = result/divisor;
                            vec.push_back(digit);
                            result -= digit * divisor;
                        }
                        return *this;
                    }
};

#endif // Integer_h
            









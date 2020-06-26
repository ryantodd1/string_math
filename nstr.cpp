#include "nstr.h"

int nstr::precision;
int nstr::disp_precision;

bool is_good_num(const std::string &str) {
    unsigned int index = 0;
    int dec = 0;
    if (str[index] == '-') index++;
    for (; index < str.size(); index++) {
        if (str[index] == '.') dec++;
        if (dec == 2) return false;
        if ((str[index] < '0' || str[index] > '9') && str[index] != '.') return false;
    }
    return true;
}

void remove_leading_zeros(std::string &str) {
    if (str.find(".") != std::string::npos) {
        while (str[0] == '0') str.erase(0, 1);
        if (str[0] == '.') str.insert(0, "0");
        return;
    }
    while (str[0] == '0') str.erase(0, 1);
}
void remove_ending_zeros(std::string &str) {
    if (str.find(".") != std::string::npos) 
        while (str[str.size() - 1] == '0') {
            str.pop_back();
            if (str[str.size() - 1] == '.') {
                str.pop_back();
                return;
            }
        }
}

bool is_zero(const std::string &str) {
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == '0' || str[i] == '.') continue;
        else return false;
    }
    return true;
}

std::string add(std::string &str1, std::string &str2) { 
    if (str1.size() > str2.size()) swap(str1, str2); 
    std::string str = ""; 
 
    int L1 = str1.size(), L2 = str2.size(); 
    int dL = L2 - L1; 
    int carry = 0; 
   
    for (int i = L1 - 1; i >= 0; i--) {  
        int sum = (str1[i] - '0') + (str2[i + dL] - '0') + carry; 
        str.push_back(sum % 10 + '0'); 
        if (sum >= 10) carry = 1;
        else carry = 0; 
    } 
   
    for (int i = L2 - L1 - 1; i >= 0; i--) { 
        int sum = ((str2[i] - '0') + carry); 
        str.push_back(sum % 10 + '0'); 
        if (sum >= 10) carry = 1;
        else carry = 0; 
    } 
  
    if (carry) str.push_back(carry + '0'); 
    reverse(str.begin(), str.end()); 
    return str;
}

std::string mul(std::string &str1, std::string &str2) {
    int L1 = str1.size(); 
    int L2 = str2.size();  
  
    std::vector<int> result(L1 + L2, 0); 
    
    int index_str1 = 0;  
    int index_str2 = 0;  
      
    for (int i = L1 - 1; i >= 0; i--) { 
        int carry = 0; 
        int L1 = str1[i] - '0'; 
        index_str2 = 0;

        for (int j = L2 - 1; j >= 0; j--) {  
            int L2 = str2[j] - '0';   
            int sum = L1 * L2 + result[index_str1 + index_str2] + carry; 
            carry = sum / 10;  
            result[index_str1 + index_str2] = sum % 10; 
            index_str2++; 
        }

        if (carry > 0) result[index_str1 + index_str2] += carry;  
        index_str1++; 
    }  
    int i = result.size() - 1; 
    while (i >= 0 && result[i] == 0) i--;  
 
    std::string s = ""; 
      
    while (i >= 0) s += std::to_string(result[i--]); 
  
    return s;
}

bool isSmaller(const std::string &str1, const std::string &str2) { 
    // Calculate lengths of both string 
    int L1 = str1.length(), L2 = str2.length(); 
  
    if (L1 < L2) return true; 
    if (L2 > L1) return false; 
  
    for (int i = 0; i < L1; i++) { 
        if (str1[i] < str2[i]) 
            return true; 
        else if (str1[i] > str2[i]) 
            return false; 
    } 
    return false; 
}

std::string sub(std::string &str1, std::string &str2) { 
    bool negative = false;
    if (isSmaller(str1, str2)) { 
        swap(str1, str2); negative = true;
    }

    std::string str = ""; 
 
    int L1 = str1.length(), L2 = str2.length(); 
    int diff = L1 - L2; 
 
    int carry = 0; 
   
    for (int i = L2 - 1; i >= 0; i--) {  
        int sub = (str1[i + diff] - '0') - (str2[i]-'0') - carry; 
        if (sub < 0) { 
            sub = sub + 10; 
            carry = 1; 
        } 
        else carry = 0; 
        str.push_back(sub + '0'); 
    }  
    for (int i=L1 - L2 - 1; i >= 0; i--) { 
        if (str1[i] == '0' && carry) { 
            str.push_back('9'); 
            continue; 
        } 
        int sub = (str1[i] - '0') - carry; 
        if (i > 0 || sub > 0) str.push_back(sub + '0'); 
        carry = 0; 
    } 
    reverse(str.begin(), str.end()); 
    if (negative) str.insert(0, "-");
    return str;
}

nstr::nstr() {
    number = "0";
    neg = false;
    if (!nstr::precision) { nstr::precision = 10; }
    if (!nstr::disp_precision) { nstr::disp_precision = 10; }
}

nstr::nstr(const char *c_str) {
    if (!is_good_num(c_str)) {
        std::cout << "\nUnable to determine numerical value in \"nstr::nstr(const char*)\"\n";
        std::cout << "Error in: nstr(\"" << c_str << "\")\n\n";
        exit(-1);
    }
    if (c_str[0] == '-') neg = true;
    else neg = false;
    number = c_str;
    if (neg) number.erase(0,1);
    if (!nstr::precision) { nstr::precision = 10; }
    if (!nstr::disp_precision) { nstr::disp_precision = 10; }
}

nstr::nstr(const std::string &str) {
    if (!is_good_num(str)) {
        std::cout << "\nUnable to determine numerical value in \"nstr::nstr(const std::string&)\"\n";
        std::cout << "Error in: nstr(\"" << str << "\")\n\n";
        exit(-1);
    }
    if (str[0] == '-') neg = true;
    else neg = false;
    number = str;
    if (neg) number.erase(0,1);
    if (!nstr::precision) { nstr::precision = 10; }
    if (!nstr::disp_precision) { nstr::disp_precision = 10; }
}

nstr::nstr(const nstr &str) {
    number = str.number;
    neg = str.neg;
    if (!nstr::precision) { nstr::precision = 10; }
    if (!nstr::disp_precision) { nstr::disp_precision = 10; }
}

nstr::~nstr() {}

void nstr::set_precision(int n) {
    if (n < 0) {
		std::cout << "\nError invalid precision in \"nstr::set_precision(int)\"\n\n";
		exit(-1);
	}
    nstr::precision = n;
}
void nstr::set_disp_precision(int n) {
    if (n <= 0) {
		std::cout << "\nError invalid precision in \"nstr::set_disp_precision(int)\"\n\n";
		exit(-1);
	}
    nstr::disp_precision = n;
}

std::ostream& operator<<(std::ostream &stream, nstr str) {
    if (str.neg) stream << "-"; 
    if (str.number.find(".") == std::string::npos) {
        stream << str.number;
        return stream;
    }
    int L = str.number.size() - str.number.find(".") - 1;
    if (L > nstr::disp_precision) {
        for (int i = 0; i <= (int)str.number.find(".") + nstr::disp_precision; i++) {
            stream << str.number[i];
        }
    }
    else stream << str.number;
    return stream;
}

nstr operator+(const nstr &str0, const nstr &str1) {
    std::string temp_str0 = str0.number;
    std::string temp_str1 = str1.number;

    remove_leading_zeros(temp_str0);
    remove_leading_zeros(temp_str1);

    int dec_length0;
    int dec_length1;

    if (temp_str0.find(".") == std::string::npos) dec_length0 = 0;
    else dec_length0 = temp_str0.size() - temp_str0.find(".") - 1;

    if (temp_str1.find(".") == std::string::npos) dec_length1 = 0;
    else dec_length1 = temp_str1.size() - temp_str1.find(".") - 1;

    while (dec_length0 > dec_length1) {
        temp_str1.append("0");
        dec_length1++;
    }
    while (dec_length1 > dec_length0) {
        temp_str0.append("0");
        dec_length0++;
    }

    if (temp_str0.find(".") != std::string::npos) 
        temp_str0.erase(temp_str0.find("."), 1);
    if (temp_str1.find(".") != std::string::npos) 
        temp_str1.erase(temp_str1.find("."), 1);

    std::string sum;

    if (!str0.neg && !str1.neg) sum = add(temp_str0, temp_str1);
    if (!str0.neg &&  str1.neg) sum = sub(temp_str0, temp_str1);
    if (str0.neg  && !str1.neg) sum = sub(temp_str1, temp_str0);
    if (str0.neg  &&  str1.neg) sum = "-" + add(temp_str0, temp_str1);
    if (dec_length0 > 0) sum.insert(sum.size() - dec_length0, ".");
    return nstr(sum);
}

nstr operator*(const nstr &str0, const nstr &str1) {
    bool negative = false;
    std::string temp_str0 = str0.number;
    std::string temp_str1 = str1.number;

    if (str0.neg && !str1.neg) negative = true;
    if (!str0.neg && str1.neg) negative = true;

    if (is_zero(temp_str1) || is_zero(temp_str0))
        return nstr("0");

    unsigned int dec_length0;
    unsigned int dec_length1;
    unsigned int total_dec_length;

    if (temp_str0.find(".") == std::string::npos) dec_length0 = 0;
    else dec_length0 = temp_str0.size() - temp_str0.find(".") - 1;

    if (temp_str1.find(".") == std::string::npos) dec_length1 = 0;
    else dec_length1 = temp_str1.size() - temp_str1.find(".") - 1;

    total_dec_length = dec_length0 + dec_length1;

    if (temp_str0.find(".") != std::string::npos) 
        temp_str0.erase(temp_str0.find("."), 1);
    if (temp_str1.find(".") != std::string::npos) 
        temp_str1.erase(temp_str1.find("."), 1);

    remove_leading_zeros(temp_str0);
    remove_leading_zeros(temp_str1);

    std::string prod = mul(temp_str0, temp_str1);
    if (is_zero(prod)) {
        std::cout << "Returning zero\n";
        return nstr("0");
    }
    if (total_dec_length > 0) {
        if (prod.size() > total_dec_length) {
            prod.insert(prod.size() - total_dec_length, ".");
        }
        else {
            for (unsigned int i = prod.size(); i < total_dec_length; i++) {
                prod.insert(0, "0");
            }
            prod.insert(0, "0.");
        }
    }

    if (prod.find(".") != std::string::npos) {
        int dec_pos = prod.find(".");
        int dec_L = prod.size() - dec_pos - 1;
        if (dec_L > nstr::precision) {
            prod.erase(dec_pos + nstr::precision + 1, std::string::npos);
        }
    }
    remove_ending_zeros(prod);
    if (negative) prod.insert(0, "-");
    return nstr(prod);
}

nstr operator-(const nstr &str0, const nstr &str1) {
    std::string temp_str0 = str0.number;
    std::string temp_str1 = str1.number;

    remove_leading_zeros(temp_str0);
    remove_leading_zeros(temp_str1);

    int dec_length0;
    int dec_length1;

    if (temp_str0.find(".") == std::string::npos) dec_length0 = 0;
    else dec_length0 = temp_str0.size() - temp_str0.find(".") - 1;

    if (temp_str1.find(".") == std::string::npos) dec_length1 = 0;
    else dec_length1 = temp_str1.size() - temp_str1.find(".") - 1;

    while (dec_length0 > dec_length1) {
        temp_str1.append("0");
        dec_length1++;
    }
    while (dec_length1 > dec_length0) {
        temp_str0.append("0");
        dec_length0++;
    }

    if (temp_str0.find(".") != std::string::npos) 
        temp_str0.erase(temp_str0.find("."), 1);
    if (temp_str1.find(".") != std::string::npos) 
        temp_str1.erase(temp_str1.find("."), 1);
    
    std::string diff;
    if (!str0.neg && !str1.neg) diff = sub(temp_str0, temp_str1);
    if (!str0.neg &&  str1.neg) diff = add(temp_str0, temp_str1);
    if (str0.neg  && !str1.neg) diff = "-" + add(temp_str1, temp_str0);
    if (str0.neg  &&  str1.neg) diff = sub(temp_str1, temp_str0);

    if (dec_length0 > 0) diff.insert(diff.size() - dec_length0, ".");

    remove_ending_zeros(diff);
    return nstr(diff);
}

nstr operator/(const nstr &str0, const nstr &str1) {
    if (is_zero(str1.number)) {
        std::cout << "\nError division by zero in \"operator/(const nstr&, const nstr&)\"\n\n";
        exit(-1);
    }
    bool negative = false;
    if (str0.neg && !str1.neg) negative = true;
    if (!str0.neg && str1.neg) negative = true;
    
    std::string temp_x = "0.";
    for (int i = 1; i < nstr::precision - 1; i++)
        temp_x.push_back('0');
    temp_x.push_back('1');

    nstr x(temp_x);
    nstr temp_str1(str1.number);
    nstr prev_x;

    do {
        prev_x = x;
        x = x * ("2" - temp_str1 * x);
        if ((temp_str1 * x > "2") || (temp_str1 * x < "-2")) {
            std::cout << "\nDivision error\n";
            std::cout << "Recomend increasing precision\n";
            std::cout << "Operation in question: \"" << str0 << " / " << str1 << "\"\n\n";
            exit(-1);
        }
    } while (prev_x != x);
        

    std::string div = (str0 * x).number;
    if (negative) div.insert(0, "-");
    
    return nstr(div);
}

nstr operator+(const char *str0, const nstr &str1) {
    nstr temp_str0(str0);
    return temp_str0 + str1;
}

nstr operator*(const char *str0, const nstr &str1) {
    nstr temp_str0(str0);
    return temp_str0 * str1;
}

nstr operator-(const char *str0, const nstr &str1) {
    nstr temp_str0(str0);
    return temp_str0 - str1;
}

nstr operator/(const char *str0, const nstr &str1) {
    if (is_zero(str1.number)) {
        std::cout << "\nError division by zero in \"operator/(const char*, const nstr&)\"\n\n";
        exit(-1);
    }
    nstr temp_str0(str0);
    return temp_str0 / str1;
}

nstr operator+(const nstr &str0, const char *str1) {
    nstr temp_str1(str1);
    return temp_str1 + str0;
}

nstr operator*(const nstr &str0, const char *str1) {
    nstr temp_str1(str1);
    return temp_str1 * str0;
}

nstr operator-(const nstr &str0, const char *str1) {
    nstr temp_str1(str1);
    return str0 - temp_str1;
}

nstr operator/(const nstr &str0, const char *str1) {
    if (is_zero(str1)) {
        std::cout << "\nError division by zero in \"operator/(const nstr&, const nstr&)\"\n\n";
        exit(-1);
    }
    nstr temp_str1(str1);
    return str0 / temp_str1;
}

bool operator==(const nstr &str0, const nstr &str1) {
    return ((str0.number == str1.number) && (str0.neg == str1.neg));
}

bool operator!=(const nstr &str0, const nstr &str1) {
    return ((str0.number != str1.number) || (str0.neg != str1.neg));
}

bool operator>=(const nstr &str0, const nstr &str1) {
    if (str0.neg && !str1.neg) return false;
    if (!str0.neg && str1.neg) return true;
    if (str0.neg)
        return ((str0.number == str1.number) || (str0.number < str1.number));
    return ((str0.number == str1.number) || (str0.number > str1.number));
}

bool operator<=(const nstr &str0, const nstr &str1) {
    if (str0.neg && !str1.neg) return true;
    if (!str0.neg && str1.neg) return false;
    if (str0.neg)
        return ((str0.number == str1.number) || (str0.number > str1.number));
    return ((str0.number == str1.number) || (str0.number < str1.number));
}

bool operator>(const nstr &str0, const nstr &str1) {
    if (str0.neg && !str1.neg) return false;
    if (!str0.neg && str1.neg) return true;
    if (str0.neg)
        return (str0.number < str1.number);
    return (str0.number > str1.number);
}

bool operator<(const nstr &str0, const nstr &str1) {
    if (str0.neg && !str1.neg) return true;
    if (!str0.neg && str1.neg) return false;
    if (str0.neg)
        return (str0.number > str1.number);
    return (str0.number < str1.number);
}

bool operator==(const char *str0, const nstr &str1) {
    nstr tstr0(str0);
    return ((tstr0.number == str1.number) && (tstr0.neg == str1.neg));
}

bool operator!=(const char *str0, const nstr &str1) {
    nstr tstr0(str0);
    return ((tstr0.number != str1.number) || (tstr0.neg != str1.neg));
}

bool operator>=(const char *str0, const nstr &str1) {
    nstr tstr0(str0);
    if (tstr0.neg && !str1.neg) return false;
    if (!tstr0.neg && str1.neg) return true;
    if (tstr0.neg)
        return ((tstr0.number == str1.number) || (tstr0.number < str1.number));
    return ((tstr0.number == str1.number) || (tstr0.number > str1.number));
}

bool operator<=(const char *str0, const nstr &str1) {
    nstr tstr0(str0);
    if (tstr0.neg && !str1.neg) return true;
    if (!tstr0.neg && str1.neg) return false;
    if (tstr0.neg)
        return ((tstr0.number == str1.number) || (tstr0.number > str1.number));
    return ((tstr0.number == str1.number) || (tstr0.number < str1.number));
}

bool operator>(const char *str0, const nstr &str1) {
    nstr tstr0(str0);
    if (tstr0.neg && !str1.neg) return false;
    if (!tstr0.neg && str1.neg) return true;
    if (tstr0.neg)
        return (tstr0.number < str1.number);
    return (tstr0.number > str1.number);
}

bool operator<(const char *str0, const nstr &str1) {
    nstr tstr0(str0);
    if (tstr0.neg && !str1.neg) return true;
    if (!tstr0.neg && str1.neg) return false;
    if (tstr0.neg)
        return (tstr0.number > str1.number);
    return (tstr0.number < str1.number);
}

bool operator==(const nstr &str0, const char *str1) {
    nstr tstr1(str1);
    return ((str0.number == tstr1.number) && (str0.neg == tstr1.neg));
}

bool operator!=(const nstr &str0, const char *str1) {
    nstr tstr1(str1);
    return ((str0.number != tstr1.number) || (str0.neg != tstr1.neg));
}

bool operator>=(const nstr &str0, const char *str1) {
    nstr tstr1(str1);
    if (str0.neg && !tstr1.neg) return false;
    if (!str0.neg && tstr1.neg) return true;
    if (str0.neg)
        return ((str0.number == tstr1.number) || (str0.number < tstr1.number));
    return ((str0.number == tstr1.number) || (str0.number > tstr1.number));
}

bool operator<=(const nstr &str0, const char *str1) {
    nstr tstr1(str1);
    if (str0.neg && !tstr1.neg) return true;
    if (!str0.neg && tstr1.neg) return false;
    if (str0.neg)
        return ((str0.number == tstr1.number) || (str0.number > tstr1.number));
    return ((str0.number == tstr1.number) || (str0.number < tstr1.number));
}

bool operator>(const nstr &str0, const char *str1) {
    nstr tstr1(str1);
    if (str0.neg && !tstr1.neg) return false;
    if (!str0.neg && tstr1.neg) return true;
    if (str0.neg)
        return (str0.number < tstr1.number);
    return (str0.number > tstr1.number);
}

bool operator<(const nstr &str0, const char *str1) {
    nstr tstr1(str1);
    if (str0.neg && !tstr1.neg) return true;
    if (!str0.neg && tstr1.neg) return false;
    if (str0.neg)
        return (str0.number > tstr1.number);
    return (str0.number < tstr1.number);
}

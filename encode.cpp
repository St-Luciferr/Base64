#include<iostream>
#include<bitset>
#include<string>
#include<fstream>
//base64 characters in order.
std::string encoded="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//convert bitset into ascii value.
int bin2ascii(char a[6],unsigned int len)
{
int sum=0;
if (a[0]=='1')sum+=32;
if (a[1]=='1'&& len>1)sum+=16;
if (a[2]=='1'&& len>2)sum+=8;
if (a[3]=='1'&& len>3)sum+=4;
if (a[4]=='1'&& len>4)sum+=2;
if (a[5]=='1'&& len>5)sum+=1;
return sum;
}

//read the characters from instring and converts into the bitset of 8 bits and write streams in a outfile
void textToBits(std::string instring, std::ofstream &outfile)
{
    for (int i=0;i<instring.length();i++)
    {
        std::bitset<8> x(instring[i]);
        outfile<<x;
    }
}

//read the bitsets and convert to base64 code for each 6bits group and return the resulting string.
std::string bitsToBase64(std::ifstream &infile)
{
    int ind;
    int  bytes=0;
    char *c=new char[6];
    std::string retstring;
    while (!infile.eof())
    {
        bytes++;
        infile.get(c,7);
        ind=bin2ascii(c,infile.gcount());
        retstring.push_back(encoded[ind]);
    }
    if (bytes%4 !=0)
    {
        for(int i=0; i<(4-bytes%4);i++)retstring.push_back('=');
    }
    return retstring;
}
int main( )
{
std::string s, retstring;
std::cout<<"enter string to encode: ";
getline(std::cin,s);
std::ofstream file;
file.open("temp.txt");
textToBits(s,file);
file.close();
std::ifstream in("temp.txt");
retstring=bitsToBase64(in);
in.close();
remove("temp.txt");
std::cout<<retstring<<"\n";
return 0;
}
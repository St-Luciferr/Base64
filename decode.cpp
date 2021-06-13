#include<iostream>
#include<bitset>
#include<string>
#include<fstream>
//base64 characters in order.
std::string encoded="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 

//convert bitset into ascii value.
int bin2ascii(char a[8],unsigned int len)
{
int sum=0;
if (a[0]=='1')sum+=128;
if (a[1]=='1'&& len>1)sum+=64;
if (a[2]=='1'&& len>2)sum+=32;
if (a[3]=='1'&& len>3)sum+=16;
if (a[4]=='1'&& len>4)sum+=8;
if (a[5]=='1'&& len>5)sum+=4;
if (a[6]=='1'&& len>6)sum+=2;
if (a[7]=='1'&& len>7)sum+=1;
return sum;
}
//read the given encoded file and writes bitset for each character into temp file
void readcode(std::ifstream &infile,std::ofstream &outfile)
{
    char a;
    int ind;
    std::string retstring;
    while (!infile.eof())
    {
        infile.get(a);
        if (a=='=')
        continue;
        ind = encoded.find(a);
        std::bitset<6> inbits(ind);
        outfile<<inbits;
    }
}

//decode the bitset into original string
std::string decode(std::ifstream &infile)
{
    char *c=new char[8];
    int asciiValue;
    unsigned char a;
    std::string retstring;
    while(!infile.eof())
    {
        infile.get(c,9);
        asciiValue=bin2ascii(c,infile.gcount());
        a =asciiValue;
        retstring.push_back(a);
    }
    return retstring;
}
int main()
{
    std::string fname,decoded;
    std::cout<<"enter filename: ";
    getline(std::cin,fname);
    std::ifstream infile(fname.c_str());
    std::ofstream outfile("temp.txt");
    readcode(infile,outfile);
    outfile.close();
    infile.close();
    infile.open("temp.txt");
    decoded=decode(infile);
    infile.close();
    std::cout<<decoded<<"\n";
    remove("temp.txt");
    return 0;
}
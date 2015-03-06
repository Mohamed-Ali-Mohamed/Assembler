#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
bool NO;
long long tonumber(string str)
{
	stringstream ss;
	ss << str;
	long long n;
	ss >>n;
	return n;
}
struct Line
{
	string LineNumber,Function,Symbol,Value,Hex_Code,Binary_Cod;
};
vector<Line>V;
string HexInc(string s)
{
	int d=1;
	string out="";
	char arr[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(int i=s.size()-1 ; i>=0 ; i--)
	{
		if(i==s.size()-1 || d!=0)
		{
			for(int j=0 ; j<16 ; j++)
			{
				if(s[i]==arr[j])
				{
					if(j<15)
					{
						out+=arr[j+d];
						d=0;
					}
					else
					{
						d=1;
						out+=arr[0];
					}
					break;
				}
			}
		}
		else
		{
			out+=s[i];
		}
	}
	if(d==1)
		out+=arr[1];
	reverse(out.begin(),out.end());
	return out;
}
string HEX_To_BIN(string s)
{
	char HEX[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	string BIN[]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
	string out="";
	for(int i=0 ; i<s.size() ; i++)
	{
		for(int j=0 ; j<16 ; j++)
		{
			if(s[i]==HEX[j])
			{
				out+=BIN[j];
				if(i<s.size()-1)out+=" ";
				break;
			}
		}
	}
	return out;
}
string DEC_To_BIN(string s)
{
	int N=tonumber(s);
	bool Neg=false;
	if(N<0){Neg=true;N*=-1;}
	string out="";
	while (N)
	{
		out+=((N%2)+'0');
		N/=2;
	}
	int SIZE=out.size();
	for(int i=SIZE ; i<16 ; i++)
	{
		out+='0';
	}
	reverse(out.begin(),out.end());
	if(Neg)
	{
		for(int i=out.size() ; i>=0 ; i--)
		{
			if(out[i]=='1')
			{
				while(i>0)
				{
					i--;
					if(out[i]=='0')out[i]='1';
					else out[i]='0';
				}
			}
		}
	}
	return out;
}
string DEC_To_HEX(string s)
{
	string _BIN=DEC_To_BIN(s);
	string out="",A="";
	char HEX[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	string BIN[]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
	for(int i=0 ; i<=_BIN.size() ; i++)
	{
		if(i%4==0 && i!=0)
		{
			for(int j=0 ; j<16 ; j++)
			{
				if(A==BIN[j])
				{
					out+=HEX[j];
					A="";
				}
			}
			
		}
		if(i<_BIN.size())
		A+=_BIN[i];
	}
	return out;
}
string BIN_To_HEX(string s)
{
	string out="",A="";
	char HEX[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	string BIN[]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1111"};
	for(int i=0 ; i<s.size() ; i++)
	{
		if(i%4==0 && i!=0)
		{
			for(int j=0 ; j<16 ; j++)
			{
				if(A==BIN[j])
				{
					out+=HEX[j];
				}
				A="";
			}
			A+=BIN[i];
		}
	}
	return out;
}
void code()
{
	string Register_Reference_Symbol[]={"CLA","CLE","CMA","CME","CIR","CIL","INC","SPA","SNA","SZA","SZE","HLT"};
	string Register_Reference_Value[]={"7800","7400","7200","7100","7080","7040","7020","7010","7008","7004","7002","7001"};
	string Input_Output_Symbol[]={"INP","OUT","SKI","SKO","ION","IOF"};
	string Input_Output_Value[]={"F800","F400","F200","F100","F080","F040"};
	string Memory_Reference_Symbol[]={"AND","ADD","LDA","STA","BUN","BSA","ISZ"};
	NO=false;
	for(int i=0 ; i<V.size() ; i++)
	{
		bool found=false;
		for(int j=0 ; j<12 && !found ; j++)
		{
			if(V[i].Symbol==Register_Reference_Symbol[j])
			{
				V[i].Hex_Code=Register_Reference_Value[j];
				V[i].Binary_Cod=HEX_To_BIN(V[i].Hex_Code);
				found=true;
			}
		}
		for(int j=0 ; j<6 && !found ; j++)
		{
			if(V[i].Symbol==Input_Output_Symbol[j])
			{
				V[i].Hex_Code=Input_Output_Symbol[j];
				V[i].Binary_Cod=HEX_To_BIN(V[i].Hex_Code);
				found=true;
			}
		}
		for(int j=0 ; j<7 && !found ; j++)
		{
			if(V[i].Symbol==Memory_Reference_Symbol[j])
			{
				V[i].Hex_Code=(j+'0');
				bool F=false;
				for(int k=0 ; k<V.size() ; k++)
				{
					if(V[k].Function==(V[i].Value+","))
					{
						F=true;
						V[i].Hex_Code+=V[k].LineNumber;
						break;
					}
				}
				if(!F)
				{
					break;
				}
				V[i].Binary_Cod=HEX_To_BIN(V[i].Hex_Code);
				found=true;
			}
		}
		if(!found)
		{
			if(V[i].Symbol=="HEX")
			{
				V[i].Hex_Code=V[i].Value;
				if(V[i].Hex_Code=="0")V[i].Hex_Code="0000";
				V[i].Binary_Cod=HEX_To_BIN(V[i].Hex_Code);
			}
			else if(V[i].Symbol=="DEC")
			{
				V[i].Hex_Code=DEC_To_HEX(V[i].Value);
				V[i].Binary_Cod=HEX_To_BIN(V[i].Hex_Code);
			}
			else if(V[i].Symbol=="BIN")
			{
				V[i].Hex_Code=BIN_To_HEX(V[i].Value);
				V[i].Binary_Cod=V[i].Value;
			}
			else
			{
				if(V[i].Symbol=="END")
					break;
				if(V[i].Symbol=="ORG")
					continue;
				V[i].Hex_Code="ERROR";
				NO=true;
			}
		}
	}
}
int main()
{
	freopen("Input.txt","r",stdin);
	freopen("Output.txt","w",stdout);
	string L,A,B,C;
	Line oneline;
	while (getline(cin,L))
	{
		A=B=C="";
		for(int i=0 ; i<L.size() ; i++)
		{
			if(A=="" && L[i]!=' ')
			{
				while (i<L.size() && L[i]!=' ')
				{
					A+=L[i++];
				}
			}
			else if(B=="" && L[i]!=' ')
			{
				while (i<L.size() && L[i]!=' ')
				{
					B+=L[i++];
				}
			}
			else if(C=="" && L[i]!=' ')
			{
				while (i<L.size() && L[i]!=' ')
				{
					C+=L[i++];
				}
			}
		}
		for(int i=0 ; i<A.size() ; i++)
		{
			if(A[i]==';')
			{
				A.erase(i,A.size());
				B=C="";
			}
		}
		for(int i=0 ; i<B.size() ; i++)
		{
			if(B[i]==';')
			{
				B.erase(i,B.size());
				C="";
			}
		}
		for(int i=0 ; i<C.size() ; i++)
		{
			if(C[i]==';')
				C.erase(i,C.size());
		}
		if(A.size()>0 && A[A.size()-1]==',')
		{
			oneline.Function=A;
			oneline.Symbol=B;
			oneline.Value=C;
		}
		else
		{
			oneline.Symbol=A;
			oneline.Value=B;
			oneline.Function=C;
		}
		if(A=="" && B=="" && C=="")
			continue;
		V.push_back(oneline);
	}
	for(int i=0 ; i<V.size() ; i++)
	{
		if(i==0)
		{
			if(V[i].Symbol=="ORG")
			{
				V[i+1].LineNumber=V[i].Value;
				i++;
			}
			else
				V[i].LineNumber="000";
		}
		else if(V[i].Symbol=="END")
			break;
		else
			V[i].LineNumber=HexInc(V[i-1].LineNumber);
	}
	code();
	/////output
	if(NO)
	{
		cout<<"Error in lines:-\n";
		for(int i=0 ;  i<V.size() ; i++)
		{
			if(V[i].Symbol=="ORG" || V[i].Symbol=="END")
					continue;
			if(V[i].Hex_Code=="ERROR")
				cout<<i+1<<endl;
		}
	}
	for(int i=0 ; !NO && i<V.size() ; i++)
	{
		cout<<V[i].LineNumber<<"\t"<<V[i].Function<<"\t"<<V[i].Symbol<<"\t"<<V[i].Value<<"\t"<<V[i].Hex_Code<<"\t"<<V[i].Binary_Cod<<endl;
	}
}
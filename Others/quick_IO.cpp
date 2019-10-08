//按ctrl+z结束输入才能看到结果
const int SIZ=100000 +3;
char buf1[SIZ];
char *p1=buf1,*p2=buf1;
inline char getcharEx(){
	if (p1==p2) p1=buf1,p2=buf1+fread(buf1,1,SIZ,stdin);
	return p1==p2?EOF:*p1++;
}
template <class T>
inline void read(T &x){
	static char ch;static bool f;
	for (ch=f=0;ch<'0' ||'9'<ch;f|=ch=='-',ch=getcharEx());
	for (x=0;'0'<=ch&&ch<='9';x=((x+(x<<2))<<1)+ch-'0',ch=getcharEx());
	x=f?-x:x;
}

template <class T>
inline void write(T x){
    if (x<0) putchar('-'),x=-x;
    if (x>=10) write(x/10);
    putchar(x%10+'0');
}

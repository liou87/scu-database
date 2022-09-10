//用成员函数重载 
#include<iostream>
using namespace std;

class Complex
{
	public:
		Complex(int real,int image)
		{
			this->real=real;
			this->image=image;
		}
		int Getreal(void)
		{
			return real;
		}
		int Getimage(void)
		{
			return image;
		}
		void show();
		Complex operator+(Complex a);
		Complex operator-(Complex a);
		Complex operator*(Complex a);
		Complex operator/(Complex a);
		Complex operator++();   //前缀++ 
		Complex operator++(int);//后缀++ 
	private:
		int real;
		int image;
};

Complex Complex::operator+(Complex a)
{
	real+=a.Getreal();
	image+=a.Getimage();
	return *this;
}
Complex Complex::operator-(Complex a)
{
	real-=a.Getreal();
	image-=a.Getimage();
	return *this;
}
Complex Complex::operator*(Complex a)
{   int x=real;
	real=real*a.Getreal()-image*a.Getimage();
	image=(x*a.Getimage())+image*a.Getreal();
	return *this;
}
Complex Complex::operator/(Complex a)
{
	Complex b(real,image);
	int y=a.Getreal()*b.Getreal()+a.Getimage()*b.Getimage();
	int z=a.Getimage()*b.Getimage()-a.Getreal()*b.Getimage();
	int x=(a.Getreal())*(a.Getreal())+(a.Getimage())*(a.Getimage());
	real=y/x;
	image=z/x;
	return *this;
}
Complex Complex::operator++()
{
	real++;
	image++;
	return *this;
}
Complex Complex::operator++(int)
{
	Complex temp(real,image);
	real++;
	image++;
	return temp;
}
void Complex::show()
 {
 	cout<<real<<" "<<image<<endl;
 }
int main()
{
	for(;;)
	{
		int a,b;
	cin>>a>>b;
	string e;
	cin>>e;
	if(e=="+")
	{
		int c,d;
		cin>>c>>d;
		Complex p(a,b),q(c,d),r(0,0);
		r=p+q;
		r.show();
	}
	else if(e=="-")
	{
		int c,d;
		cin>>c>>d;
		Complex p(a,b),q(c,d),r(0,0);
		r=p-q;
		r.show();
	}
	else if(e=="*")
	{
		int c,d;
		cin>>c>>d;
		Complex p(a,b),q(c,d),r(0,0);
		r=p*q;
		r.show();
	}
	else if(e=="/")
	{
	int c,d;
		cin>>c>>d;
		Complex p(a,b),q(c,d),r(0,0);
		r=p/q;
		r.show();
    }
    else if(e=="++1")
    {
    	Complex p(a,b);
    	++p;
    	p.show();
	}
	else if(e=="++2")
	{
		Complex p(a,b);
    	p++;
    	p.show();
	}
	}
	
	
}

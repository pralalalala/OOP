

#include"Container.h"
#include"Classes.h"
#include<iostream>

int main()
{
	Classes::Component* NordGuild = new Classes::DK; // класс ДК

	MyList<Classes::DK> list = MyList<Classes::DK>();

	MyList<Classes::DK>::iterator it = list.begin();




	return 42;
}

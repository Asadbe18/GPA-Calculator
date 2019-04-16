#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
int scount=0,gcount=0; //loop counter for no. of subject and grading
     
	 /* defining
      structure data types */

struct student_record
{
	string name;
	string courses[10];
	int semester;
	double marks [10]={0};
	double C_GPA=0;
}; student_record sr; //declaring global variable for student record

struct grading
{
		double gradingarray[10][10]; //grading array for 3 or 2credit hours
		double gradingarray1[10][10]; //grading array for 1 credit hours
		double GPA_CH[10][10]={{0}};  //gpa of subjects and their respective credit hours
		int min_pmarks=60; //min passing marks
};  grading gr; //declaring global variable for grading

     /* declaring 
      and 
     defining Fucntions  */

void credits() //function for credits
{
		cout<<"*"<<setfill('-')<<setw(40)<<"*"<<endl;
		cout<<"* Compiled by:\n*\tAsad Majeed\n*\tBE-II\n*\tSukkur IBA University "<<endl;
		cout<<"*"<<setfill('-')<<setw(40)<<"*"<<endl;
}

void getcourses_and_ch()
{
	    ifstream data;
		if (sr.semester==1) //if semester=1 
		 {
		   data.open("semester 1.txt");	//opening 1st semester courses
		   if (data.fail())
		   cout<<"Error!\n Semester 1 File could not be opened."<<endl;
	     }
	    else
	    if (sr.semester==2) //if semester is 2
	     {
	     	data.open("semester 2.txt"); //opening semester 2 file
	     	if (data.fail())  //if file fails to open
		   cout<<"Error!\n Semester 2 File could not be opened."<<endl;
		 }
		 
		int i=0; 
		scount=0; //setting scount to zero
		while(!data.eof())
		{
			getline(data,sr.courses[i]); //getting course name
	        data>>gr.GPA_CH[i][i+1]; //for storing credit hours of courses in 2nd column of marks array
	        data.ignore();
	        ++i;
	        ++scount;
		}
		data.close();
}

void gradingfunc() //checking for grading policy
{
	    gcount=0; //setting gcount to zero
	    int i=0;
		ifstream data,data1;
		data.open("grading policy.txt"); //opening grading policy file for checking grades for 3 credit hour courses
		if (data.fail()) //if file fails to open
		{
			cout<<"Error!\n Grading Policy(3) Not Found."<<endl;
		}
		data1.open("grading policy2.txt"); //opening grading policy file for checking grades for 3 credit hour courses
			if (data.fail()) //if file fails to open
		{
			cout<<"Error!\n Grading Policy(1) Not Found."<<endl;
		}
		while (!data.eof())
		{
	    	data>>gr.gradingarray[i][0]; //storing percentage
		    data.ignore();
		    data>>gr.gradingarray[i][i+1]; //storing corresponding gpa
		
		    data1>>gr.gradingarray1[i][0]; //storing percentage
		    data1.ignore();
		    data1>>gr.gradingarray1[i][i+1]; //storing corresponding gpa
		    ++gcount;
		    ++i;
	    }
	    data.close();
	    data1.close();
}

void gpacalculator() //function for calculating gpa of each subject
{
 for (int i=0;i<scount;i++) //for loop for assigning gpa
  { //Start of for loop body
  	    gr.GPA_CH[i][0]=sr.marks[i]; //saving marks in gpa's first coloumn
	    if (gr.GPA_CH[i][i+1]==2) //if course is of 2 credit hours
	    gr.GPA_CH[i][0]*=2; //doubling its percentage for comparing it
	    
	  if (gr.GPA_CH[i][i+1]==3 || gr.GPA_CH[i][i+1]==2) //checking for credit hours for assinging of gpa
		{
		       if (gr.GPA_CH[i][0]<gr.min_pmarks) //for checking passing marks
		       {
		       		gr.GPA_CH[i][0]=0; //setting gpa to zero
	    	        continue; //continue to next itteration
			   }
			for (int j=0;j<gcount;j++) //loop for checking and assingning gpa
			    {
			      if (gr.GPA_CH[i][0]>=gr.gradingarray[j][0]) //matching percentage for grading
			        {
				       gr.GPA_CH[i][0]=gr.gradingarray[j][j+1]; //assigning gpa
				       break; 
		            }
	            }
        } //end of if body
    else
    if (gr.GPA_CH[i][i+1]==1) //checking for credit hours for assinging of gpa
    {
    	     if (gr.GPA_CH[i][0]<gr.min_pmarks/2) //for checking passing marks
		       {
		       		gr.GPA_CH[i][0]=0; //setting gpa to zero
	    	        continue; //continue to next itteration
			   }
             for (int j=0;j<gcount;j++) //loop for checking and assingning gpa
	           {
	            	if (gr.GPA_CH[i][0]>=gr.gradingarray1[j][0]) //matching percentage for grading
	   	            {
	   	            gr.GPA_CH[i][0]=gr.gradingarray1[j][j+1]; //assigning gpa
	   	            break;
	                }
	            }	
	} //end of else body
  } //end of for loop body
} //end of graidng function

void cgpacounter() //function for counting cgpa
{
	double temp1=0,temp2=0,temp=0;
	for (int i=0;i<scount;i++)
	{
		temp=gr.GPA_CH[i][0]; //storing gpa in temp
		temp*=gr.GPA_CH[i][i+1]; //multiplying it by its credit hours
		temp1+=temp; // sum of gpa's point
		temp2+=gr.GPA_CH[i][i+1]; //sum of credit hours
	}
	sr.C_GPA=temp1/temp2; //dividing total points by total credit hours
}

void print () //function for printing course gpa's
{
	cout<<"Result Card: "<<endl;
	cout<<"\t\t\tSemester "<<sr.semester<<endl;
	for (int i=0;i<scount;i++)
	{
	cout<<sr.courses[i]<<"\n\t\t Marks: "<<sr.marks[i]<<"\t GPA: "<<gr.GPA_CH[i][0]<<endl;
    }
    cout<<"\t\tCGPA of Semester: "<<sr.C_GPA<<endl<<endl;
    
    if (sr.C_GPA>=3.3)
    cout<<"Excellent "<<sr.name<<",\n Keep Striving for Excellence. :)"<<endl;
    else 
    if (sr.C_GPA>=3.00)
    cout<<"Good Job "<<sr.name<<",\n Keep it up and Continue your Efforts. :) "<<endl;
    else 
    if (sr.C_GPA<3.00)
    cout<<"Pretty Well "<<sr.name<<",\n Work Hard."<<endl;
    cout<<"*"<<setfill('-')<<setw(80)<<"*"<<endl;
}

void semesters();

/*  Main function */

int main()
{
	cout<<"Enter Your Name: "<<endl;
	getline(cin,sr.name);
	do
	{
	cout<<"Enter 0 for Credits of the Program "<<endl;
	cout<<"Enter 1 to find CGPA for Semester I\nEnter 2 to find CGPA of Semester II  ";
	cin>>sr.semester;
	switch (sr.semester)
	{
		case 1:
		case 2:
			semesters(); //function calling
			break;
		case 0:
			credits(); //function calling
			break;
		default:
		cout<<"Wrong input try again\n";
	}
     cout<<"Enter any number to continue again\nEnter 9 to terminate: ";
     	cin>>sr.semester;
    }
    while (sr.semester!=9);
	return 0;
}

void semesters()
{
	int temp=0; //declaring and initilizing temp
	getcourses_and_ch(); //fuction calling for courses and credit hours
	double cv=0; //declaring check variable
	cout<<"\nEnter 0.0 for using back button "<<endl;
	cout<<"\t\tSemester "<<sr.semester<<endl; //for semester 1
	for (int i=0;i<scount;i++)
	{
		cout<<"Enter Your Marks in "<<sr.courses[i]<<" : ";
		cin>>cv;
		while(((cv>100||cv<0)&&gr.GPA_CH[i][i+1]==3)||((cv>50||cv<0)&&(gr.GPA_CH[i][i+1]==2||gr.GPA_CH[i][i+1]==1)))  //if user inputs exceeds the limit
		{
			cout<<"Wrong Input"<<endl<<"Enter Your Marks in "<<sr.courses[i]<<endl;
			cin>>cv;
		}
		if (cv==0.0)
		{
			if (i==0) //for back button
			main(); //calling main function
			else
		    {
			----i;  //decriment
			continue;
		    }
		}
		temp=cv;
		if (cv-temp>=0.5) //for rounding off the number;
		temp=ceil(cv); //using ceil function
		sr.marks[i]=temp; //assingning marks to marks array
		temp=0; //destroying temp value
	}
		gradingfunc();     //function calling
		gpacalculator();
		cgpacounter();
		print();
		scount=0;
		gcount=0;
}//end of semester function

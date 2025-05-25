#include <iostream>
#include <string>//for space in name
#include <windows.h>// for system cls
#include<fstream> // for file reding and writing
#include<vector>// for storing questions
#include <algorithm> // for std::shuffle
#include <random>     //  for shuffle
#include <limits>  //  for ignoring input buffer
using namespace std;
struct Question{ // used for representing single guestions from txt file
    string questiontext;
    string optionA;
    string optionB;
    string optionC;
    string optionD;
    string correctoption;
   
   
    void displayQuestion(){  //used for the display format(how the questions will be displayed)
   cout << questiontext << endl;
    cout<<"  A"<<optionA<<endl;
    cout<<"  B"<<optionB<<endl;
    cout<<"  C"<<optionC<<endl;
    cout<<"  D"<<optionD<<endl;
   }
};
  class Quizgame{  //is used to keep all the things under one structure
   private:
   vector<Question> ListOfQuestion;  //it will store the data after the fileload is completed
   int score;
   int numberOfQuestionsAsked; //  initialize for the questions asked from the total number of questions

   public://The constructor runs when an object of Quizgame is created. It sets the score to 0 and loads the file.
   Quizgame(){
    score=0;
    numberOfQuestionsAsked = 0; 
    fileload(); // to load all the data which is being fetched from the below code


   }


   void fileload(){
    ListOfQuestion.clear(); //  clear previous questions on replay
    ifstream fin("question.txt");  //for file reading and fin(object) for passing info 
    Question ques; // for loading question
    if(fin.is_open()){// to open the file
        while (getline(fin,ques.questiontext)) //tell where you want to place the data
        {
            getline(fin,ques.optionA);
            getline(fin,ques.optionB);
            getline(fin,ques.optionC);
            getline(fin,ques.optionD);
            getline(fin,ques.correctoption);
            ListOfQuestion.push_back(ques); // for loading data after reading

        }
         
        random_device rd; // it is used for getting questions randomly on screen
        mt19937 g(rd());
        shuffle(ListOfQuestion.begin(), ListOfQuestion.end(), g);
        fin.close(); //used for closing the file
    }else{
        cout<<"file not found"<<endl;
    }


   }
    
  void StartQuiz(int numberOfQuestions = 10){
    numberOfQuestionsAsked=numberOfQuestions;
    int count=0;
    for(auto& Q : ListOfQuestion) //it will get quetions from listofquestions 
    {
     if(count>=numberOfQuestions)   break;
     Q.displayQuestion(); // for displaing question on console
     string answer;
     cout<<"enter your answer  :" ;
     getline(cin,answer);//for getting answer fron user and storing it in answer variable
     if (toupper(answer[0]) == toupper(Q.correctoption[0])){
        score++;
     cout<<"correct answer"<<endl;
    
    }else{
        cout<<"wrong answer!"<<endl;
    }
    count++;
    }
  }
  void displayresult(){
    system("cls");
    cout << "total score " << score << "/" << numberOfQuestionsAsked << endl;

  }
   int getScore() {
        return score;
    }

};
void saveHighScore(string name, int score) { // we are using this function for saving high score 
    ifstream fin("highscore.txt");
    string highScorer;
    int highScore = 0;

    if (fin.is_open()) {// OPENS THE EXISTING FILE reads the high score and closes the file
        fin >> highScore;
        fin.ignore(); // skip newline
        getline(fin, highScorer);
        fin.close();
    }

    if (score > highScore) {//if new  score is higher than the existing one it open the file and saves the new score and scorer and closes the file
        ofstream fout("highscore.txt");
        fout << score << endl << name;
        fout.close();
    }
}

void displayHighScore() { // for displaying high score on console 
    ifstream fin("highscore.txt");
    string name;
    int score;

    if (fin.is_open()) {// opens the file reas the score and name 
        fin >> score;
        fin.ignore();
        getline(fin, name);
        cout << "\n\n===== Highest Score =====" << endl;
        cout << "Name  : " << name << endl;
        cout << "Score : " << score << endl;
        cout << "=========================\n" << endl;
        fin.close();
    } else {
        cout << "\nNo high score found yet.\n" << endl;
    }
}




   int main() {
    char choice;
    string name;
    int Enrollment;

    do {
        
        cout << "\n\n\t\t************" << endl;
        cout << "\t\t  Quiz  Game " << endl;
        cout << "\t\t************" << endl;
        cout << "1. Play Quiz\n2. View High Score\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// it is a way to clear the input buffer so that the next input operation (especially getline) works correctly.

        if (choice == '1') {
            cout << "\t\t Enter Your Name: ";
            getline(cin, name);
            cout << "\t\t Enter Your Enrollment: ";
            cin >> Enrollment;
            cin.ignore(); // clear newline

            Quizgame qa;
            qa.StartQuiz(10);
            qa.displayresult();
         saveHighScore(name, qa.getScore());  // record high score
        } else if (choice == '2') {
            displayHighScore();
        } else if (choice == '3') {
            cout << "Thanks for playing!" << endl;
            break;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }

        cout << "Press 'Y' or 'y' to go back to menu, or any other key to exit: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (choice == 'y' || choice == 'Y');

    return 0;
}


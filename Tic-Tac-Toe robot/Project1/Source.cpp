#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "string"

using namespace cv;
using namespace std;

void draw_board(int *b) {
	int k = 0;
	cout << "----++---++----" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << "| ";
			if (b[k] == 0) {
				cout << k + 1 << " |";
			}
			else {
				if (b[k] == -1) {
					cout << "X |";
				}
				else {
					cout << "O |";
				}
			}
			k++;
		}
		cout << "\n----++---++----" << endl;
	}
}

int win(int *board) {
	//determines if a player has won, returns 0 otherwise.
	int wins[8][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
	for (int i = 0; i < 8; i++) {
		if (board[wins[i][0]] != 0 &&
			board[wins[i][0]] == board[wins[i][1]] && board[wins[i][1]] == board[wins[i][2]])
			return board[wins[i][2]];
	}
	return 0;
}

int minimax(int *board, int player) {
	int winner = win(board);

	if (winner != 0)
		return winner * player;

	int move = -1;
	int score = -2;

	for (int i = 0; i < 9; i++) {

		if (board[i] == 0) {

			board[i] = player;
			int thisScore = -minimax(board, player*-1);

			if (thisScore > score) {
				score = thisScore;
				move = i;
			}
			board[i] = 0;
			//Reset board after try
		}
	}
	if (move == -1)
		return 0;

	return score;
}

int computerMove(int *board) {
	int move = -1;
	int score = -2;

	for (int i = 0; i < 9; i++) {

		if (board[i] == 0) {
			board[i] = 1;
			int tempScore = -minimax(board, -1);
			board[i] = 0;

			if (tempScore > score) {
				score = tempScore;
				move = i;
			}
		}
	}
	//returns a score based on minimax tree at a given node.
	return move;
}
int ImageCapture(int *board , int photoPlace )
{
	string name[18], address[18], imageName, imageAddress;
	name[0] = "image1.JPG";
	name[1] = "image2.JPG";
	name[2] = "image3.JPG";
	name[3] = "image4.JPG";
	name[4] = "image5.JPG";
	name[5] = "image6.JPG";
	name[6] = "image7.JPG";
	name[7] = "image8.JPG";
	name[8] = "image9.JPG";
	name[9] = "image10.JPG";
	name[10] = "image11.JPG";
	name[11] = "image12.JPG";
	name[12] = "image13.JPG";
	name[13] = "image14.JPG";
	name[14] = "image15.JPG";
	name[15] = "image16.JPG";
	name[16] = "image17.JPG";
	name[17] = "image18.JPG";
	address[0] = "E:/project1/Project1/Project1/image1.JPG";
	address[1] = "E:/project1/Project1/Project1/image2.JPG";
	address[2] = "E:/project1/Project1/Project1/image3.JPG";
	address[3] = "E:/project1/Project1/Project1/image4.JPG";
	address[4] = "E:/project1/Project1/Project1/image5.JPG";
	address[5] = "E:/project1/Project1/Project1/image6.JPG";
	address[5] = "E:/project1/Project1/Project1/image7.JPG";
	address[7] = "E:/project1/Project1/Project1/image8.JPG";
	address[8] = "E:/project1/Project1/Project1/image9.JPG";
	address[9] = "E:/project1/Project1/Project1/image10.JPG";
	address[10] = "E:/project1/Project1/Project1/image11.JPG";
	address[11] = "E:/project1/Project1/Project1/image12.JPG";
	address[12] = "E:/project1/Project1/Project1/image13.JPG";
	address[13] = "E:/project1/Project1/Project1/image14.JPG";
	address[14] = "E:/project1/Project1/Project1/image15.JPG";
	address[15] = "E:/project1/Project1/Project1/image16.JPG";
	address[16] = "E:/project1/Project1/Project1/image17.JPG";
	address[17] = "E:/project1/Project1/Project1/image18.JPG";
	imageName = name[photoPlace];
	imageAddress = address[photoPlace];

		VideoCapture cap(1);
		if (!cap.isOpened())
			return (-1);
		Mat image;
		while (true) {
			Mat frame;
			cap.read(frame);
			imshow("Camera", frame);
			if (waitKey(3000000) == 's')
			{
				image = frame.clone();
				resize(image, image, Size(), 0.65, 0.65);
				imshow("image", image);
				imwrite(imageName , image);
			}
			else if (waitKey(30) == 'd') 
				break;
			break;
		}
		Mat image2;
		image2 = imread(imageAddress , 0);
		imshow("image2", image2);
		resize(image2, image2, Size(), 0.65, 0.65);
		vector<Vec3f> coin;
		HoughCircles(image2, coin, HOUGH_GRADIENT, 2, 30, 450, 60, 14, 20);
		int l = coin.size();

		cout << "\n The number of coins is: " << l << "\n\n";

		for (size_t i = 0; i < coin.size(); i++)
		{
			Point center(cvRound(coin[i][0]), cvRound(coin[i][1]));
			int radius = cvRound(coin[i][2]);
			circle(image2, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			circle(image2, center, radius, Scalar(0, 0, 255), 3, 8, 0);
			cout << " Center location for circle " << i + 1 << " :" << center << "\n Diameter : " << 2 * radius << "\n";
			//cell 1
			if (coin[i][0] >= 15 && coin[i][0] <= 79 && coin[i][1] >= 21 && coin[i][1] <= 59)
			{
				board[0] = -1;
				//cout << "cell 1";
			}
			//cell 2
			else if (coin[i][0] >= 105 && coin[i][0] <= 167 && coin[i][1] >= 25 && coin[i][1] <= 59)
			{
				board[1] = -1;
				//cout << "cell 2";
			}
			//cell 3
			else if (coin[i][0] >= 203 && coin[i][0] <= 255 && coin[i][1] >= 21 && coin[i][1] <= 59)
			{
				board[2] = -1;
				//cout << "cell 3";
			}
			//cell 4
			else if (coin[i][0] >= 15 && coin[i][0] <= 81 && coin[i][1] >= 81 && coin[i][1] <= 121)
			{
				board[3] = -1;
				//cout << "cell 4";
			}
			//cell 5
			else if (coin[i][0] >= 107 && coin[i][0] <= 171 && coin[i][1] >= 87 && coin[i][1] <= 117)
			{
				board[4] = -1;
			}
			//cell 6
			else if (coin[i][0] >= 197 && coin[i][0] <= 257 && coin[i][1] >= 87 && coin[i][1] <= 119)
			{
				board[5] = -1;
			}
			//cell 7
			else if (coin[i][0] >= 15 && coin[i][0] <= 79 && coin[i][1] >= 149 && coin[i][1] <= 181)
			{
				board[6] = -1;
			}
			//cell 8
			else if (coin[i][0] >= 107 && coin[i][0] <= 167 && coin[i][1] >= 151 && coin[i][1] <= 175)
			{
				board[7] = -1;
			}
			//cell 9
			else if (coin[i][0] >= 197 && coin[i][0] <= 255 && coin[i][1] >= 149 && coin[i][1] <= 175)
			{
				board[8] = -1;
			}
		}
		cout << "\n";
		draw_board(board);
		namedWindow("Coin Counter", WINDOW_AUTOSIZE);
		imshow("Coin Counter", image2);

		waitKey(30);
	return *board;

}
int main()
{
	int moves = 0, photoPlace = 0;
	int board[9] = { 0 }, Lastboard[9] = { 0 };
	draw_board(board);
	while (moves < 9) {
		for (int i = 0; i < 9; i++)
		{
			Lastboard[i] = board[i];
		}

		ImageCapture(board , photoPlace );
		photoPlace++;
		int userMove = -1, k;
  //      for (int i = 0; i < 9; i++)
		//{
		//	cout << board[i] << " " ;
		//}
		//cout << endl;
		//for (int i = 0; i < 9; i++)
		//{
		//	cout << Lastboard[i] << " " ;
		//}
		//cout << endl;
		for (int i = 0; i < 9; i++)
		{
			if (Lastboard[i] != board[i])
			{
				userMove = i + 1;
				break;
			}
		}
		if (Lastboard[userMove - 1] == 0)
		{
			Lastboard[userMove - 1] = -1;
			moves++;
			if (win(board)==0)
			{
				k = computerMove(board);
				board[k] = 1;
				draw_board(board);
				moves++;
				if (win(board) != 0) {
					break;
				}
			}
			else
				break;
		}
		else {
			cout << "Illegal Move, Try again !! \n\n";
		}
	}
	switch (win(board)) {
	case 0:
		cout << "Its a draw. Better Smart next time.\n";
		break;
	case 1:
		cout << "You lose.\n";
		break;
	case -1:
		cout << "This will never Happen. But if it does(It never will), Congratulations, You have beaten the unbeatable\n";
		break;
	}
	system("pause");
	return 0;
}
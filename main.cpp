#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

/*
  Name: Helen Wang
  Date: Mar 3, 2023
  Program: Heap, insert and store numbers into a max heap by user or file.
  Can delete the largest element or all at once. 
 */

void insert(int* heap, int num);
void printTree(int* heap, int depth, int index);
void printList(int* heap);
void deleteAll(int* heap);
void deleteRoot(int* heap, int index);


int main() {

  bool playing = true;
  char command[15];
  int* heap = new int[101];
  int size = 0;

  //clear out array
  for(int i = 1; i < 101; i++) {
    heap[i] = 0;
  }
  
  while (playing == true) {
    //User chooses to insert, remove, print or quit
    cout << "commands: insert, remove, print or quit" << endl;
    cin.get(command, 15, '\n');
    cin.ignore();

    if (strcmp(command, "insert") == false) {
      cout << "Add 'manually' or from 'file'?" << endl;
      cin.get(command, 15, '\n');
      cin.ignore();

      if (strcmp(command, "manually") == false || strcmp(command, "man") == false) {
	int num;
	cout << "Manually enter in number: ";
	cin >> num;
	cin.ignore();
	insert(heap, num);
      }
      else if (strcmp(command, "file") == false) {
	char* fileName = new char[20];
	int* output = new int[100];

	for(int i=0; i < 1000; i++) {
	  output[i] = 0;
	}
	
	cout << "Type file name: (include '.txt')" << endl;
	cin.get(fileName, 20, '\n');
	cin.ignore();
	ifstream file;
	file.open(fileName);

	//extract numbers from file
	int input = 0;
	int inputNum = 1;
	while (file >> input) {
	  insert(heap, input);
	  inputNum++;
	}
	file.close();
      }
    }

    else if (strcmp(command, "remove") == false) {
      cout << "Remove 'all' or 'largest' element(s)" << endl;
      cin.get(command, 15, '\n');
      cin.ignore();

      if (strcmp(command, "all") == false) {
	int index = 1;
	//while heap is not empty yet, keep deleting the largest element
	while(heap[index] != 0) {
       	  deleteRoot(heap, index);
	}
      }

      else if (strcmp(command, "largest") == false) {
	deleteRoot(heap, 1);
      }
    }

    else if (strcmp(command, "print") == false) {
      int inputNum = 1;
      cout << "list format: " << endl;
      printList(heap);
      cout << endl;

      cout << "tree format: " << endl;
      cout << endl;
      printTree(heap, 0, 1);
    }

    else if (strcmp(command, "quit") == false) {
      playing = false;
    }

    else {
      cout << "Please enter in a valid command" << endl;
    }
  }
}

//insert a number into the heap
void insert(int* heap, int num) {
  int count = 1;
  int temp = 0;

  //if array is empty, insert number into first slot
  if (heap[1] == 0) {
    heap[1] = num;
    //cout << "helen"<<endl;
  }
  
  //else, swap with parent if bigger
  else {
    //cout << "hi" << endl;
    while(heap[count] != 0) {
      count++;
    }
    heap[count] = num;
    cout << heap[count] << " ";
  
    while(heap[count] > heap[count/2]&& count!=1) {
      temp = heap[count/2];
      heap[count/2] = heap[count];
      heap[count] = temp;
      //cout << "i: " << count << "num: " << heap[count]<<endl;
      count = count/2; 
    }
  }
}

//print numbers as a list 
void printList(int* heap) {
  for(int i = 1; i < 101; i++) {
    if (heap[i] != 0) {
      cout << heap[i] << " ";
    }
  }
}

//print numbers in a tree format
void printTree(int* heap, int depth, int index) {

  //parent to the left, children to the right of parents
  if (heap[1] != 0) {
    if(heap[1] == 0) {
      index++;
    }
    
    if(heap[index * 2 + 1] != 0) {
      printTree(heap, depth + 1, index*2+1);
    }
    
    for (int i = 0; i < depth; i++) {
      cout << "\t";
    }
    
    cout << heap[index] << endl;
    
    if (heap[index * 2] != 0) {
      printTree(heap, depth + 1, index*2);
    }
  }
}

//delete the largest element of the array
void deleteRoot(int* heap, int index) {
  //cout << "root: " << heap[1] << endl;

    int size = 1;
    cout << "beginning index: " << index << endl;
  //Get last value
  while(heap[size] !=0) {
    size++;
  }

  size = size-1;

  int bigger = 0;
  int r = index;
  
  heap[index] = heap[size];
  heap[size] = 0;

  //move last value to root
  
  //cout << "before while loop" << endl;
  //cout << "index: " << index << endl;
  //cout << "heap[index]: " << heap[index] << endl;
  //cout << "left: " << heap[index*2] << endl;
  //cout << "right: " << heap[index*2+1] << endl;
  
  while((heap[r] < heap[r * 2]) || (heap[r] < heap[r * 2 + 1])) {
    //swap current with larger of left/right
    //current is now the one you swapped with

    //if left is bigger than right, replace root with left
    if (heap[r * 2] > heap[r * 2 +1]) {
      //heap[1] = heap[index * 2];
      //heap[index] = heap[index*2];
      int temp = heap[r];
      heap[r] = heap[r*2];
      heap[r*2] = temp;
      cout << "left" << endl;
      r = r*2;
    }

    //if right is bigger than left, replace root with right
    else if (heap[r * 2 +1] > heap[r *2]) {
      //heap[1] = heap[index * 2 +1];
      //heap[index] = heap[index*2+1];
      int temp1 = heap[r];
      heap[r] = heap[r*2+1];
      heap[r*2+1] = temp1;
      cout << "right" << endl;
      r = r*2+1;
    }
    cout << "hi"<< endl;
    cout << "index: " << index << endl;
  }

  printList(heap);
}


/*
void heapify(int* heap, int size, int index) {
  int temp = index;
  if(index*2+1 < size && heap[temp] < heap[index*2+1]) {
    temp = index*2+1; 
  }
  if (index*2+2 < size && heap[temp] < heap[index*2+2]) {
    temp = index*2+2;
  }
  if (temp != index) {
    int temp1 = heap[temp];
    heap[temp] = heap[index];
    heap[index] = temp1;
    heapify(heap, size, temp);
  }
}

void deleteRoot(int* heap, int &size) {
  for (int i =0; i < size; size--) {
    cout << heap[1] << ","; //print root
    heap[1] = heap[size-1]; //replace last element with root
    heapify(heap, size, 0);
    heap[size-1] = 0; //set last element to "NULL"
  }
}
*/

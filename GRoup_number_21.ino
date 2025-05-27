// Define a Node structure
struct Node {
  int data;
  char carecter;
  Node* next;
};

// Define a LinkedList class
class LinkedList {
public:
  LinkedList() : head(nullptr) {}

  // Insert a new element at the beginning of the list
  void insert(int id,char charecter) {
    Node* newNode = new Node;
    newNode->data = id;
    newNode->carecter = charecter;
    newNode->next = head;
    head = newNode;
  }

  // Print the elements of the list
  void print() {
    Node* current = head;
    while (current != nullptr) {
      Serial.print(current->data);
      Serial.print(" ");
      current = current->next;
    }
    Serial.println();
  }

  char search(int id){
     Node* current = head;
     while(current != nullptr){
      // thresh hold for mis
      if((current->data)>id-100 || ((current->data)<id+100 )){
          return current->carecter;
      }
      else{
        current = current->next;
      }
     }
     return '\0';
     
  }
private:
  Node* head;
};

// Example usage
LinkedList myList;

const int analogPins[] = {A0, A1, A2, A3};
const int digitalPins[] = {2, 3, 4, 5, 6};

const String welcomeNote = "--------------------------------------\nආයුබෝවන්, මම Echo. ඔබගේ කතන සහයක. \nWelcome, I am Echo. you speak companian.\n--------------------------------------";
const int default_enable = 0;

const String startActionNote = "-------------------------------\nලිඛිත අකාරය ක්‍රියාත්මකයි. \nWriting Mode On\n--------------------------------";
const int action_enable = 1;
const String startActionKey = "Hi";

const String startTestNote = "--------------------------------------\nපරික්ෂණ ආකාරය ක්‍රියාත්මකයි. \n Test Mode on.\n--------------------------------------";
const int test_enable = 2;
const String startTestKey = "Test";

const String leaveNote = "--------------------------------------\nස්තුති. ඉක්මනින් නැවත හමුවෙමු. \n Thank you. see you soon.\n--------------------------------------";
const String leaveKey = "Bye";

float analogReading[] = {0,0,0,0};
int digitalReading[] = {0,0,0,0,0};

int reading = 0;
char oldReading = '\0';

int enabled = default_enable;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0;i<4;i++){
    pinMode(analogPins[i],INPUT);
  }
  for(int i = 0;i<5;i++){
    pinMode(digitalPins[i],INPUT);
  }

  Serial.begin(9600);
  Serial.println(welcomeNote);
  sampleLoad();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  String action = "";
  if(Serial.available()){
    action = Serial.readString();
  }

  if(action.startsWith(startActionKey)){
    enabled = action_enable;
    Serial.println(startActionNote);
  }
  
  if(action.startsWith(leaveKey)){
    enabled = default_enable;
    Serial.println(leaveNote);
  }
  if(action.startsWith(startTestKey)){
    enabled = test_enable;
    Serial.println(startTestNote);
  }
  

  if(enabled==test_enable){
    reading = getTesting();
    Serial.println(reading);
  } else if(enabled==action_enable){
    reading = getReading();
    char charecter = myList.search(reading);
    if(charecter != oldReading && charecter != '\0'){
      oldReading = charecter;
      if(charecter != '\t') Serial.print(charecter);
      else if(charecter == '\t') Serial.print(" ");
    }
  }
  

  
  
}

int getTesting(){

  int combinedValue = 0;
  for(int i = 0;i<4;i++){
    
    analogReading[i] = map(analogRead(analogPins[i]), 0, 1023, 0, 8);
    Serial.print("f");
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(analogReading[i]);
    Serial.print(", ");
    
  }

  int digitalValues = 0;
  for(int i = 0;i<5;i++){
    
    digitalReading[i] = digitalRead(digitalPins[i]);
    Serial.print("d");
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(digitalReading[i]);
    Serial.print(", ");
    digitalValues |= digitalRead(digitalPins[i]) << i;
 
    
    for (int i = 0; i < 4; i++) {
      combinedValue = combinedValue * 10 + analogReading[i];
    }
      combinedValue = combinedValue * 10000 + digitalValues;
    }

  return combinedValue;
}

int getReading(){

  for(int i = 0;i<4;i++){
    
    analogReading[i] = map(analogRead(analogPins[i]), 0, 1023, 0, 8);
  }

  int digitalValues = 0;
  for(int i = 0;i<5;i++){
    
    digitalReading[i] = digitalRead(digitalPins[i]);
    digitalValues |= digitalRead(digitalPins[i]) << i;
  }
  
  int combinedValue = 0;
  for (int i = 0; i < 4; i++) {
    combinedValue = combinedValue * 10 + analogReading[i];
  }
  combinedValue = combinedValue * 10000 + digitalValues;

  return combinedValue;
}

void loadValue(){
  myList.insert(28723,'a');
  myList.insert(-19220,'b');
  myList.insert(-2914,'c');
  myList.insert(18910,'d');
  myList.insert(-23570,'e');
  myList.insert(-12453,'f');
  myList.insert(30327,'g');
  myList.insert(-19220,'h');
  myList.insert(-15909,'i');
  myList.insert(-23142,'j');
  myList.insert(-28390,'k');
  myList.insert(30430,'l');
  myList.insert(10448,'m');
  myList.insert(12504,'n');
  myList.insert(-275250,'o');
  myList.insert(-25202,'p');
  myList.insert(29050,'q');
  myList.insert(4918,'r');
  myList.insert(13514,'s');
  myList.insert(-2518,'t');
  myList.insert(6974,'u');
  myList.insert(-20840,'v');
  myList.insert(21086,'w');
  myList.insert(-7974,'x');
  myList.insert(30327,'y');
  myList.insert(21292,'z');
  myList.insert(-11301,'\t');
}

void sampleLoad(){
  myList.insert(11324,'a');
  myList.insert(24865,'b');
  myList.insert(28062,'d');
  myList.insert(-20721,'o');
  myList.insert(-25202,'p');
  myList.insert(-23570,'e');
  myList.insert(269923,'f');
}









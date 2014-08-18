
//shalom
//M247,27.5c0,78.294-58,79-58,0
//M218.5,86L218.5,28
//M124.067,18c16.555,0,6.816,13.976,0,13.976c-7.79,0-5.328,11.305,33.337,0C196.07,20.67,164.257,84.029,125.184,86
//M96.088,28c5.883,0,8.089,37.707,8.089,58.486
//M32.509,32.531c11.073-12.947,33.264-7.632,40.795-0.427   c7.53,7.205,11.297,38.685,0,49.932c-11.298,11.248-32.635,10.092-40.795,0C24.351,71.944,24.351,42.07,32.509,32.531z
String svg = "M247,27.5c0,78.294-58,79-58,0M218.5,86L218.5,28M124.067,18c16.555,0,6.816,13.976,0,13.976c-7.79,0-5.328,11.305,33.337,0C196.07,20.67,164.257,84.029,125.184,86M96.088,28c5.883,0,8.089,37.707,8.089,58.486M32.509,32.531c11.073-12.947,33.264-7.632,40.795-0.427c7.53,7.205,11.297,38.685,0,49.932c-11.298,11.248-32.635,10.092-40.795,0C24.351,71.944,24.351,42.07,32.509,32.531";


void drawSVG(){
  
  Serial.println("Drawing SVG");    

  while (svg.length() > 0){
    
    String type = svg.substring(0,1);
    svg = svg.substring(1);
    
    char opts[] = {'c','C','m','M','l','L'};
    
    int next = svg.length();
    for (int i=0; i < 6; i++){
      int c = svg.indexOf(opts[i]);
      if (c!=-1 && c<next) next=c;
    }

    String data = svg.substring(0,next);
    svg = svg.substring(next);
    
    drawSection(type, data);
      
  }

}

void drawSection(String type, String data){

  if (print_parsing){
    Serial.print("Drawing Section: ");    
    Serial.print(type);    
    Serial.print(" | ");    
    Serial.println(data);    
  }
  double x[3];
  double y[3];
  
  for (int i=0; i<3; i++){
    
    //parse each set of x,y
    char opts[] = {',',' ','-'};
    int nextX = data.length();
    for (int i=0; i < 3; i++){
      int c = data.indexOf(opts[i], 1);
      if (c!=-1 && c<nextX) nextX=c;
    }
    int nextY = data.length();
    for (int i=0; i < 3; i++){
      int c = data.indexOf(opts[i], (nextX+1));
      if (c!=-1 && c<nextY) nextY=c;
    }
    
    int skipX = 1;
    if (data[nextX]=='-') skipX = 0;
    int skipY = 1;
    if (data[nextY]=='-') skipY = 0;

    char nums[16];
    if (nextY > 0){
      data.substring(0,nextX).toCharArray(nums, 8);
      x[i] = atof(nums);
      data.substring(nextX+skipX, nextY).toCharArray(nums, 8);
      y[i] = atof(nums);
      data = data.substring(nextY+skipY);
    }else if (data.length() > 0){
      data.substring(0,nextX).toCharArray(nums, 8);
      x[i] = atof(nums);
      data.substring(nextX+skipX).toCharArray(nums, 8);
      y[i] = atof(nums);
      data = "";
    }else{
      x[i] = -1;
      y[i] = -1;
    }
    
    if (print_parsing){
      Serial.print("Parsing: ");    
      Serial.print(nextX);    
      Serial.print(" | ");    
      Serial.print(nextY);    
      Serial.print(" | ");    
      Serial.print(x[i]);    
      Serial.print(" | ");    
      Serial.print(y[i]);    
      Serial.print(" | ");    
      Serial.println(data);    
    }

    //normalize if needed
    if (type == "L" || type == "M" || type == "C"){
      x[i] -= curX;
      y[i] -= curY;
 
      if (print_parsing){
        Serial.print("Normalized: ");    
        Serial.print(nextX);    
        Serial.print(" | ");    
        Serial.print(nextY);    
        Serial.print(" | ");    
        Serial.print(x[i]);    
        Serial.print(" | ");    
        Serial.print(y[i]);    
        Serial.print(" | ");    
        Serial.println(data);    
     }
   }
  

  }
     
  if (print_parsing){
    if (type == "m" || type == "M"){
      Serial.print("move to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.println(" ");    
    } else if (type == "l" || type == "L"){
      Serial.print("line to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.println(" ");    
    } else if (type == "c" || type == "C"){
      Serial.print("curve to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.print(" ");    
      Serial.print(x[1]);    
      Serial.print(",");    
      Serial.print(y[1]);    
      Serial.print(" ");    
      Serial.print(x[2]);    
      Serial.print(",");    
      Serial.print(y[2]);    
      Serial.println(" ");    
    }
  }

  //draw the section
  if (type == "m" || type == "M"){
    goTo(x[0], y[0]);
  } else if (type == "l" || type == "L"){
    lineTo(x[0], y[0]);
  } else if (type == "c" || type == "C"){
    curveTo(x[0], y[0], x[1], y[1], x[2], y[2]);
  }
 
  
}


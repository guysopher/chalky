
String svg = "m79,405c100,100 343,604 798,338";//c13.20918,6.59679 25.20836,12.63287 36,19c11.22955,6.62549 21.23541,12.73578 28,19c4.15056,3.84355 7.37134,7.74675 10,12c1.17557,1.90211 2,5 2,7c0,2 1,3 1,5c0,1 0,2 0,5c0,1 0.28589,3.21167 -2,6c-0.89659,1.09367 -1.19028,2.88152 -3,6c-1.12234,1.93399 -1.85274,3.1731 -3,4c-1.814,1.30745 -2.85274,2.1731 -4,3c-1.814,1.30745 -4.31001,1.33749 -7,3c-1.203,0.7435 -3.47125,3.45877 -10,5c-2.91975,0.68925 -6.03354,3.41743 -16,6c-1.93605,0.50168 -7.07843,2.78986 -10,4c-2.06586,0.85571 -3,2 -3,2c-2,1 -2.37752,0.83058 -4,2c-2.56537,1.84901 -1.90633,4.10341 -3,5c-2.78833,2.28587 -4,2 -5,3c-1,1 -2,2 -2,2c0,1 -1,1 -2,1l0,0";

void drawSVG(){
  
    Serial.println("Drawing SVG");    

  while (svg.length() > 0){
    
    String type = svg.substring(0,1);
    svg = svg.substring(1);
    
    int next = svg.length();
    int c = svg.indexOf("c");
    if (c!=-1 && c<next) next=c;
    int l = svg.indexOf("l");
    if (l!=-1 && l<next) next=l;
    int m = svg.indexOf("m");
    if (m!=-1 && m<next) next=m;

    String data = svg.substring(0,next);
    svg = svg.substring(next);
    
    drawSection(type, data);
      
  }

}

void drawSection(String type, String data){

  if (debug){
    Serial.print("Drawing Section: ");    
    Serial.print(type);    
    Serial.print(" | ");    
    Serial.println(data);    
  }
  float x[3];
  float y[3];
  
  for (int i=0; i<3; i++){
    
    //parse each set of x,y
    int nextX = data.indexOf(",");
    int nextY = data.indexOf(" ");
    char nums[16];
      if (nextY > 0){
        data.substring(0,nextX).toCharArray(nums, 5);
        x[i] = atof(nums);
        data.substring(nextX+1, nextY).toCharArray(nums, 5);
        y[i] = atof(nums);
        data = data.substring(nextY+1);
      }else if (data.length() > 0){
        data.substring(0,nextX).toCharArray(nums, 5);
        x[i] = atof(nums);
        data.substring(nextX+1).toCharArray(nums, 5);
        y[i] = atof(nums);
        data = "";
      }else{
        x[i] = -1;
        y[i] = -1;
      }
      
      if (debug){
        Serial.print("Parsing: ");    
        Serial.print(nextX);    
        Serial.print(" | ");    
        Serial.print(nextY);    
        Serial.print(" | ");    
        Serial.println(data);    
      }
  }
     
  if (debug){
    if (type == "m"){
      Serial.print("move to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.println(" ");    
    } else if (type == "l"){
      Serial.print("line to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.println(" ");    
    } else if (type == "c"){
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
  if (type == "m"){
    goTo(x[0], y[0]);
  } else if (type == "l"){
    lineTo(x[0], y[0]);
  } else if (type == "c"){
    curveTo(x[0], y[0], x[1], y[1], x[2], y[2]);
 }
  
}


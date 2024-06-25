import processing.serial.*;

Serial myPort; 
String angle = "";
String distance = "";
int iAngle, iDistance;

void setup() {
size(1200, 700);
  smooth();
  
 
  myPort = new Serial(this, "9", 9600); //inplace of 9 the actual port that we connect
  myPort.bufferUntil('.'); 
}

void draw() {
  background(0); 
  
  fill(98, 245, 31); 
  noStroke();
  rect(0, 0, width, height - height * 0.065); 
  
  drawRadar(); 
  drawLine(); 
  drawObject(); 
  drawText(); 
}

void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('.');
  if (data != null) {
    data = data.substring(0, data.length() - 1); 
    int index = data.indexOf(",");
    angle = data.substring(0, index);
    distance = data.substring(index + 1);
    iAngle = int(angle);
    iDistance = int(distance);
  }
}

void drawRadar() {
  pushMatrix();
  translate(width / 2, height - height * 0.074); 
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);
  

  for (int i = 0; i <= 360; i += 30) {
    line(0, 0, (width / 2) * cos(radians(i)), -(width / 2) * sin(radians(i)));
  }
  
  popMatrix();
}

void drawObject() {
  if (iDistance >= 0 && iDistance <= 10) {
    stroke(255, 0, 0); //red for close onjects
  } else if (iDistance > 10 && iDistance <= 20) {
    stroke(255, 191, 0); // Orange for mid-range objects
  } else if (iDistance > 20 && iDistance <= 30) {
    stroke(255, 255, 0); // Yellow for farobjects
  } else if (iDistance > 30 && iDistance <= 40) {
    stroke(0, 255, 0); // Green for even farther objects
  } else {
    return; // Don't draw objects out of range
  }
  
  float pixsDistance = iDistance * ((height - height * 0.1666) * 0.025);
  
  pushMatrix();
  translate(width / 2, height - height * 0.074);
  strokeWeight(9);
  
  line(pixsDistance * cos(radians(iAngle)), -pixsDistance * sin(radians(iAngle)), 
       (width - width * 0.505) * cos(radians(iAngle)), -(width - width * 0.505) * sin(radians(iAngle)));
  
  popMatrix();
}

void drawLine() {
  pushMatrix();
  translate(width / 2, height - height * 0.074);
  strokeWeight(9);
  stroke(30, 250, 60); // Light green
  
  line(0, 0, (height - height * 0.12) * cos(radians(iAngle)), -(height - height * 0.12) * sin(radians(iAngle)));
  
  popMatrix();
}

void drawText() {
  pushMatrix();
  fill(98, 245, 31); // Green fill color
  noStroke();
  
  rect(0, height - height * 0.0648, width, height);
  
  textSize(25);
  for (int i = 0; i <= 360; i += 30) {
    translate((width - width * 0.4994) + width / 2 * cos(radians(i)), (height - height * 0.0907) - width / 2 * sin(radians(i)));
    rotate(-radians(-i));
    text(i + "∞", 0, 0);
    resetMatrix();
  }
  
  text("10cm", width - width * 0.3854, height - height * 0.0833);
  text("20cm", width - width * 0.281, height - height * 0.0833);
  text("30cm", width - width * 0.177, height - height * 0.0833);
  text("40cm", width - width * 0.0729, height - height * 0.0833);
  
  textSize(40);
  text("Indian Lifehacker", width - width * 0.875, height - height * 0.0277);
  text("Angle: " + iAngle + " ∞", width - width * 0.48, height - height * 0.0277);
  text("Distance: " + iDistance + " cm", width - width * 0.26, height - height * 0.0277);
  
  popMatrix();
}

paper.install(window);

Point.prototype.addScaledVector = function(vector, variable){
    this.x += (vector.x)*variable;
    this.y += (vector.y)*variable;
}
Point.prototype.multiplebyScalar = function(variable){
    this.x *= variable;
    this.y *= variable;
}

function Particle(){
    this.position = new Point();
    this.velocity = new Point();
    this.acceleration = new Point();
    /**
    * Holds the amount of damping applied to linear
    * motion. Damping is required to remove energy added
    * through numerical instability in the integrator.
    */
    this.damping = null;
    this.inverseMass = null;
    this.forceAccum = null;
    this.bindedShape = null;
}
Particle.prototype.integrate = function(duration){
    if(duration < 0.0){
        //exception
        console.log("error in duration");
    }
    // Update linear position.
    //    console.log(this.position);
    //    console.log(this.velocity);
    //    console.log(duration);
    this.position.addScaledVector(this.velocity, duration);
    //    console.log("--------------------");
    // Work out the acceleration from the force.
    var resultingAcc = this.acceleration;
    resultingAcc.addScaledVector(this.forceAccum, this.inverseMass);
    // Update linear velocity from the acceleration.
    this.velocity.addScaledVector(resultingAcc, duration);
    // Impose drag.
    this.velocity.multiplebyScalar(Math.pow(this.damping, duration));
    //    console.log(this.velocity);
    if(this.bindedShape!=null){
        this.bindedShape.position = this.position;
    }
}

window.onload = function() {
    paper.setup('canvas');
    var tool = new Tool();
    
    var frame = new Path.Rectangle(new Point(0,0),view.size);
    frame.strokeColor = 'black';
    var initialPosition = new Point(10,view.size.height-50);
    
    var myCircle = new Path.Circle(initialPosition, 5);
    myCircle.fillColor = 'black';
    

    

    

    
 
    
    var ball;
    tool.onKeyDown = function(event){
        initialPosition = new Point(10,view.size.height-50);
        if(event.character=='1'){
            var ball1 = new Particle();
            ball1.position = initialPosition;
            ball1.inverseMass = 1/2;//kg
            ball1.velocity = new Point(350,0);
            ball1.acceleration = new Point(0,10);
            ball1.damping = 0.99;
            ball1.forceAccum = new Point(0,0);
            ball1.bindedShape = myCircle;
            ball = ball1;
        }else if(event.character=='2'){
            var ball2 = new Particle();
            ball2.position = initialPosition;
            ball2.inverseMass = 1/200;//kg
            ball2.velocity = new Point(400,-300);
            ball2.acceleration = new Point(0,200);
            ball2.damping = 0.99;
            ball2.forceAccum = new Point(0,0);
            ball2.bindedShape = myCircle;
            ball = ball2;
        }else if(event.character=='3'){
            var ball3 = new Particle();
            ball3.position = initialPosition;
            ball3.inverseMass = 1;//kg
            ball3.velocity = new Point(250,0);
            ball3.acceleration = new Point(0,-30);
            ball3.damping = 0.9;
            ball3.forceAccum = new Point(0,0);
            ball3.bindedShape = myCircle;
            ball = ball3;
        }else if(event.character=='4'){
            var ball4 = new Particle();
            ball4.position = initialPosition;
            ball4.inverseMass = 10;//kg
            ball4.velocity = new Point(1000,0);
            ball4.acceleration = new Point(0,0);
            ball4.damping = 0.99;
            ball4.forceAccum = new Point(0,0);
            ball4.bindedShape = myCircle;
            ball = ball4;
        }
    }
    view.onFrame = function(event){
        if(event.delta>1){
            return;
        }
        if(ball){
            ball.integrate(event.delta);
        }
    }
    
    
    view.draw();
}
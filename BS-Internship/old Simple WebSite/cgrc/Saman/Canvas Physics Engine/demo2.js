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
    this.forceAccum = new Point(0,0);
    this.bindedShape = null;
}
Particle.prototype.integrate = function(duration){
    if(duration < 0.0){
        //exception
        console.log("error in duration");
    }
    // Update linear position.
    //        console.log(this.position.x);
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
    //    console.log(this.velocity);
    this.velocity.multiplebyScalar(Math.pow(this.damping, duration));
        
    if(this.bindedShape!=null){
        this.bindedShape.position = this.position;
    }
}

function Firework(){
    Particle.call(this);
    /** Fireworks have an integer type, used for firework rules. */
    this.type = null;
    /**
     * The age of a firework determines when it detonates. Age gradually
     * decreases; when it passes zero the firework delivers its payload.
     * Think of age as fuse-left.
     */
    this.age = null;
}
Firework.prototype = new Particle();
Firework.prototype.constructor = Firework;
/**
 * Updates the firework by the given duration of time. Returns true
 * if the firework has reached the end of its life and needs to be
 * removed.
 */
Firework.prototype.update = function(duration)
{
    // Update our physical state
    this.integrate(duration);
    // We work backward from our age to zero.
    this.age -= duration;
    return (this.age < 0);
}


/**
 * Firework rules control the length of a firework’s fuse and the
 * particles it should evolve into.
 */
function FireworkRule()
{
    /** The type of firework that is managed by this rule. */
    this.type = null;
    /** The minimum length of the fuse. */
    this.minAge = null;
    /** The maximum length of the fuse. */
    this.maxAge = null;
    /** The minimum relative velocity of this firework. */
    this.minVelocity = null;//vector
    /** The maximum relative velocity of this firework. */
    this.maxVelocity = null;//vector
    /** The damping of this firework type. */
    this.damping = null;
    
    /** The number of payloads for this firework type. */
    this.payloadCount = null;
    /** The set of payloads. */
    this.payloads = new Array();
}

/**
 * Creates a new firework of this type and writes it into the given
 * instance. The optional parent firework is used to base position
 * and velocity on.
 */
FireworkRule.prototype.create = function(parent)
{
    var firework = new Firework();
    firework.type = this.type;
    firework.age = (this.maxAge-this.minAge)*Math.random()+this.minAge;
    if (parent!=null){
        var position = new Point();
        position.x = parent.position.x;
        position.y = parent.position.y;
        firework.position = position;
        var vel = new Point();
        vel.x = parent.velocity.x;
        vel.y = parent.velocity.y;
        vel.x += (this.maxVelocity.x-this.minVelocity.x)*Math.random()+this.minVelocity.x;
        //        console.log(vel.x);
        vel.y += (this.maxVelocity.y-this.minVelocity.y)*Math.random()+this.minVelocity.y;
        //        console.log(vel.y);
        firework.velocity = vel;
    //        console.log(firework.velocity);
    } else{
        firework.position = new Point(300*Math.random()+200,650);
        var vel2 = new Point(0,0);
        vel2.x += (this.maxVelocity.x-this.minVelocity.x)*Math.random()+this.minVelocity.x;
        vel2.y += (this.maxVelocity.y-this.minVelocity.y)*Math.random()+this.minVelocity.y;
        firework.velocity = vel2;
    }
    // We use a mass of 1 in all cases (no point having fireworks
    // with different masses, since they are only under the influence
    // of gravity).
    firework.inverseMass = 1;
    firework.damping = this.damping;
    firework.acceleration = new Point(0,50);
    return firework;
}
/**
 * The payload is the new firework type to create when this
 * firework’s fuse is over.
 */
function Payload(type,count)
{
    /** The type of the new particle to create. */
    this.type = type;
    /** The number of particles in this payload. */
    this.count = count;
}
var rules = new Array();

var rule0 = new FireworkRule();
rule0.payloadCount =2;
rule0.type =1;
rule0.minAge = 0.5;
rule0.maxAge = 1.2;
rule0.minVelocity = new Point(-100,-680);
rule0.maxVelocity = new Point(100,-870);
rule0.damping = 0.15;
rule0.payloads[0] = new Payload(2,10);
rule0.payloads[1] = new Payload(3,5);

var rule1 = new FireworkRule();
rule1.payloadCount =0;
rule1.type =2;
rule1.minAge = 1.5;
rule1.maxAge = 2.5;
rule1.minVelocity = new Point(-150,150);
rule1.maxVelocity = new Point(150,-100);
rule1.damping = 0.3;

var rule2 = new FireworkRule();
rule2.payloadCount =1;
rule2.type =3;
rule2.minAge = 0.5;
rule2.maxAge = 1.2;
rule2.minVelocity = new Point(-200,-150);
rule2.maxVelocity = new Point(200,-270);
rule2.damping = 0.3;
rule2.payloads[0] = new Payload(2,9);

rules.push(rule0,rule1,rule2);

function create(type,number,parent)
{
    var color = new HsbColor(Math.random() * 360, 1, 1);
    for(var i = 0;i<number;i++){
        // Get the rule needed to create this firework.
        var rule = rules[type-1];
        // Create the firework.
        var firework = rule.create(parent);
        var myCircle = new Path.Circle(firework.position, 2);
        myCircle.fillColor = color;
        firework.bindedShape = myCircle;
        fireworks.push(firework);
    // Increment the index for the next firework.
    //nextFirework = (nextFirework + 1) % maxFireworks;
    }
}

var fireworks = new Array();


window.onload = function() {
    paper.setup('canvas');
    var tool = new Tool();
    var frame = new Path.Rectangle(new Point(0,0),view.size);
    frame.strokeColor = 'white';
    
    
    tool.onMouseDown = function(event){
        create(1,1, null);
    }
    //    console.log(fireworks);
    view.onFrame = function(event){
        if(event.delta>1){
            return;
        }
        for(var i =0 ; i< fireworks.length;i++){
            var firework = fireworks[i];
                
            if (firework.type > 0)
            {
                // Does it need removing?
                //                console.log(i);
                //                console.log(firework.velocity);
                if (firework.update(event.delta))
                {
                    var rule = rules[firework.type-1];
                    //// Delete the current firework (this doesn’t affect its
                    //// position and velocity for passing to the create function,
                    //// just whether or not it is processed for rendering or
                    //// physics.
                    firework.type = 0;
                    firework.bindedShape.remove();
                    var index = fireworks.indexOf(firework);
                    fireworks.splice(index, 1);
                    // Add the payload.
                    for (var j = 0; j < rule.payloadCount; j++)
                    {
                        var payload = rule.payloads[j];
                        create(payload.type, payload.count, firework);
                    }
                //}
                //}
                //}
                    
                }
                
                
            }
            
        }
    }
    
    view.draw();
}
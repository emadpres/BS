paper.install(window);

Point.prototype.addScaledVector = function(vector, variable){
    this.x += (vector.x)*variable;
    this.y += (vector.y)*variable;
}
Point.prototype.multiplebyScalar = function(variable){
    this.x *= variable;
    this.y *= variable;
}

Point.prototype.scalarProduct = function(vector){
    return this.x*vector.x + this.y*vector.y;
}

function Particle(radius){
    this.position = new Point(0,0);
    this.velocity = new Point(0,0);
    this.acceleration = new Point(0,0);
    this.resultAcc = null;
    /**
     * Holds the amount of damping applied to linear
     * motion. Damping is required to remove energy added
     * through numerical instability in the integrator.
     */
    this.damping = 1;
    this.inverseMass = 1/10;
    this.infiniteMass = false;
    /**
     * Holds the accumulated force to be applied at the next
     * simulation iteration only. This value is zeroed at each
     * integration step.
     */
    this.forceAccum = new Point(0,0);
    this.radius = radius;
    this.bindedShape = new Path.Circle(this.position, radius);
    this.bindedShape.fillColor = "black";
    this.name = null;
    //    this.bindedShape.strokeColor = "red";
    this.path = new Path();
    this.path.add(new Point());
    this.path.add(new Point());
}
Particle.prototype.integrate = function(duration){
    if(duration < 0){
        //exception
        console.log("error in duration");
    }
    // Update linear position.
    //        console.log(this.position);
    //    console.log(this.velocity);
    //    console.log(duration);
    
    //    console.log("v: "+this.velocity);
    this.position.addScaledVector(this.velocity, duration);
    //    console.log("--------------------");
    // Work out the acceleration from the force.
    var resultingAcc = new Point(this.acceleration.x,this.acceleration.y);
    resultingAcc.addScaledVector(this.forceAccum, this.inverseMass);
    this.resultAcc = resultingAcc;
    // Update linear velocity from the acceleration.
    this.velocity.addScaledVector(resultingAcc, duration);
    // Impose drag.
    //    console.log(this.velocity);
    this.velocity.multiplebyScalar(Math.pow(this.damping, duration));
    if(this.bindedShape!=null){
        this.bindedShape.position = this.position;
    }
    //    console.log("velocity: "+this.velocity.y+" whole force: "+this.forceAccum.y+"acc: "+ resultingAcc.y+" this.acc:"+this.acceleration.y);
    this.forceAccum.x=0;
    this.forceAccum.y=0;
    
    this.path.segments[1].point = this.position;
}
Particle.prototype.addForce = function(force){
    this.forceAccum.x += force.x;
    this.forceAccum.y += force.y;
}

function ParticleForceGenerator(){
    
}
ParticleForceGenerator.prototype.updateForce = function(particle,duration){
    }

function ParticleGravity(){
    ParticleForceGenerator.call(this);
    this.gravity = new Point(0,20);
}
ParticleGravity.prototype = new ParticleForceGenerator();
ParticleGravity.prototype.constructor = ParticleGravity;
ParticleGravity.prototype.updateForce = function(particle,duration){
    if(!particle.infiniteMass){
        particle.addForce(new Point((1/particle.inverseMass)*this.gravity.x,(1/particle.inverseMass)*this.gravity.y));
    }
}

function ParticleDrag(){
    ParticleForceGenerator.call(this);
    /** Holds the velocity drag coefficient. */
    this.k1 = 4;
    /** Holds the velocity squared drag coefficient. */
    this.k2 = 0;
}
ParticleDrag.prototype = new ParticleForceGenerator();
ParticleDrag.prototype.constructor = ParticleDrag;
ParticleDrag.prototype.updateForce = function(particle,duration){
    var force;
    force = particle.velocity;
    // Calculate the total drag coefficient.
    var dragCoeff = force.length;
    dragCoeff = this.k1 * dragCoeff + this.k2 * dragCoeff * dragCoeff;
    // Calculate the final force and apply it.
    force = force.normalize();
    force.x *= -dragCoeff;
    force.y *= -dragCoeff;
    particle.addForce(force);
//    console.log("velocity: "+particle.velocity.y+" force:"+force.y+" whole force: "+particle.forceAccum.y);
}

/**
 * Holds all the force generators and the particles they apply to.
 */
function ParticleForceRegistry(){
    /**
     * Holds the list of registrations.
     */
    this.registrations = new Array();
}
/**
 * Holds all the force generators and the particles they apply to.
 */
function ParticleForceRegistration(){
    this.particle = null;
    this.particleForceGenerator = null;
}
/**
 * Calls all the force generators to update the forces of
 * their corresponding particles.
 */
ParticleForceRegistry.prototype.updateForces = function(duration){
    for(var i=0;i<this.registrations.length;i++){
        this.registrations[i].particleForceGenerator.updateForce(this.registrations[i].particle, duration)
    }
}

/**
 * A force generator that applies a spring force.
 */
function ParticleSpring(other,springConstant,restLength){
    ParticleForceGenerator.call(this);
    /** The particle at the other end of the spring. */
    this.otherParticle = other;
    /** Holds the spring constant. */
    this.springConstant = springConstant;
    /** Holds the rest length of the spring. */
    this.restLength = restLength;
}
ParticleSpring.prototype = new ParticleForceGenerator();
ParticleSpring.prototype.constructor = ParticleSpring;

/** Applies the spring force to the given particle. */
ParticleSpring.prototype.updateForce = function(particle,duration){
    var force = new Point(particle.position.x,particle.position.y);
    force.x -= this.otherParticle.position.x;
    force.y -= this.otherParticle.position.y;
    // Calculate the magnitude of the force.
    var magnitude = force.length;
    magnitude = (magnitude - this.restLength);
    magnitude *= this.springConstant;
    // Calculate the final force and apply it.
    force = force.normalize();
    force.x *= -magnitude;
    force.y *= -magnitude;
    //    console.log(force.y);
    particle.addForce(force);
}
function ParticleBungee(other,springConstant,restLength){
    ParticleForceGenerator.call(this);
    /** The particle at the other end of the spring. */
    this.otherParticle = other;
    /** Holds the spring constant. */
    this.springConstant = springConstant;
    /** Holds the rest length of the spring. */
    this.restLength = restLength;
}
ParticleBungee.prototype = new ParticleForceGenerator();
ParticleBungee.prototype.constructor = ParticleSpring;

/** Applies the spring force to the given particle. */
ParticleBungee.prototype.updateForce = function(particle,duration){
    var force = new Point(particle.position.x,particle.position.y);
    force.x -= this.otherParticle.position.x;
    force.y -= this.otherParticle.position.y;
    // Calculate the magnitude of the force.
    var magnitude = force.length;
    if(magnitude<=this.restLength){
        return;
    }
    magnitude = Math.abs(magnitude - this.restLength);
    magnitude *= this.springConstant;
    // Calculate the final force and apply it.
    force = force.normalize();
    force.x *= -magnitude;
    force.y *= -magnitude;
    particle.addForce(force);
}


function ParticleBuoyancy(maxDepth,volume,waterHeight,liquidDensity){
    ParticleForceGenerator.call(this);
    /**
     * The maximum submersion depth of the object before
     * it generates its maximum buoyancy force.
     */
    this.maxDepth = maxDepth;
    /**
     * The volume of the object.
     */
    this.volume = volume;
    /**
     * The height of the water plane above y=0. The plane will be
     * parallel to the X axis.
     */
    this.waterHeight = waterHeight;
    /**
     * The density of the liquid. Pure water has a density of
     * 1000 kg per cubic meter.
     */
    this.liquidDensity = liquidDensity;
}
ParticleBuoyancy.prototype = new ParticleForceGenerator();
ParticleBuoyancy.prototype.constructor = ParticleBuoyancy;

/** Applies the spring force to the given particle. */
ParticleBuoyancy.prototype.updateForce = function(particle,duration){
    // Calculate the submersion depth.
    var depth = view.size.height - particle.position.y;
    // Check if we’re out of the water.
    if (depth >= this.waterHeight + this.maxDepth){
        return;
    }
    var force = new Point(0,0);
    // Check if we’re at maximum depth.
    if (depth <= this.waterHeight - this.maxDepth)
    {
        force.y = -this.liquidDensity * this.volume;
        particle.addForce(force);
        return;
    }
    // Otherwise we are partly submerged.
    force.y = -this.liquidDensity * this.volume *(-depth + this.maxDepth + this.waterHeight) / (2 * this.maxDepth);
    //    console.log(force.y);
    particle.addForce(force);
}

/**
 * A contact represents two objects in contact (in this case
 * ParticleContact representing two particles). Resolving a
 * contact removes their interpenetration, and applies sufficient
 * impulse to keep them apart. Colliding bodies may also rebound.
 *
 * The contact has no callable functions, it just holds the
 * contact details. To resolve a set of contacts, use the particle
 * contact resolver class.
 */
function ParticleContact()
{
    /**
     * Holds the particles that are involved in the contact. The
     * second of these can be NULL, for contacts with the scenery.
     */
    //of type Particle
    this.particle = new Array();

    /**
     * Holds the normal restitution coefficient at the contact.
     */
    this.restitution = null;
    /**
     * Holds the direction of the contact in world coordinates.
     */
    this.contactNormal = new Point();/**
    * Holds the depth of penetration at the contact.
    */
    this.penetration = null;
}
/**
 * Resolves this contact, for both velocity and interpenetration.
 */
ParticleContact.prototype.resolve = function(duration){
    this.resolveVelocity(duration);
    this.resolveInterpenetration(duration);
}

/**
 * Calculates the separating velocity at this contact.
 */
ParticleContact.prototype.calculateSeparatingVelocity = function(){
    var relativeVelocity = new Point(this.particle[0].velocity);
    if (this.particle[1]){
        relativeVelocity.x -= this.particle[1].velocity.x;
        relativeVelocity.y -= this.particle[1].velocity.y;
    }
    return relativeVelocity.scalarProduct(this.contactNormal);
}

/**
 * Handles the impulse calculations for this collision.
 */
ParticleContact.prototype.resolveVelocity = function(duration){
    // Find the velocity in the direction of the contact.
    var separatingVelocity = this.calculateSeparatingVelocity();
    // Check whether it needs to be resolved.
    if (separatingVelocity > 0)
    {
        // The contact is either separating or stationary - there’s
        // no impulse required.
        return;
    }
    // Calculate the new separating velocity.
    var newSepVelocity = -separatingVelocity * this.restitution;
    
    // Check the velocity build-up due to acceleration only.
    var accCausedVelocity = this.particle[0].resultAcc;
    if (this.particle[1]){
        accCausedVelocity.x -= this.particle[1].resultAcc.x;
        accCausedVelocity.y -= this.particle[1].resultAcc.y;
    }
    var accCausedSepVelocity = accCausedVelocity.scalarProduct(this.contactNormal) * duration;
    // If we’ve got a closing velocity due to acceleration build-up,
    // remove it from the new separating velocity.
    if (accCausedSepVelocity < 0)
    {
        newSepVelocity += this.restitution * accCausedSepVelocity;
        //        console.log(newSepVelocity);
        // Make sure we haven’t removed more than was
        // there to remove.
        if (newSepVelocity < 0) {
            newSepVelocity = 0;
        }
    }
    var deltaVelocity = newSepVelocity - separatingVelocity;
    // We apply the change in velocity to each object in proportion to
    // its inverse mass (i.e., those with lower inverse mass [higher
    // actual mass] get less change in velocity).
    var totalInverseMass = this.particle[0].inverseMass;
    if (this.particle[1]){
        totalInverseMass += this.particle[1].inverseMass;
    }
    // If all particles have infinite mass, then impulses have no effect.
    if (totalInverseMass <= 0) return;
    // Calculate the impulse to apply.
    var impulse = deltaVelocity / totalInverseMass;
    // Find the amount of impulse per unit of inverse mass.
    var impulsePerIMass = new Point(this.contactNormal.x * impulse,this.contactNormal.y * impulse);
    // Apply impulses: they are applied in the direction of the contact,
    // and are proportional to the inverse mass.console.log(impulsePerIMass.x * this.particle[0].inverseMass);
    //    console.log(this.particle[0].velocity.x);
    this.particle[0].velocity.x = this.particle[0].velocity.x + impulsePerIMass.x * this.particle[0].inverseMass;
    //    console.log(impulsePerIMass.x * this.particle[0].inverseMass);
    //    console.log(this.particle[0].velocity.x);
    this.particle[0].velocity.y = this.particle[0].velocity.y + impulsePerIMass.y * this.particle[0].inverseMass;
    if (this.particle[1])
    {
        // Particle 1 goes in the opposite direction.
        this.particle[1].velocity.x = this.particle[1].velocity.x + impulsePerIMass.x * -this.particle[1].inverseMass;
        this.particle[1].velocity.y = this.particle[1].velocity.y + impulsePerIMass.y * -this.particle[1].inverseMass;
    
    }
}
/**
* Handles the interpenetration resolution for this contact.
*/
ParticleContact.prototype.resolveInterpenetration = function(duration){
    // If we don’t have any penetration, skip this step.
    //    console.log("p "+this.penetration);
    if (this.penetration <= 0) return;
    // The movement of each object is based on its inverse mass, so
    // total that.
    var totalInverseMass = this.particle[0].inverseMass;
    if (this.particle[1]){
        totalInverseMass += this.particle[1].inverseMass;
    }
    // If all particles have infinite mass, then we do nothing.
    if (totalInverseMass <= 0) return;
    // Find the amount of penetration resolution per unit of inverse mass.
    var movePerIMass = new Point(this.contactNormal.x *(this.penetration / totalInverseMass),this.contactNormal.y *(-this.penetration / totalInverseMass));
    // Apply the penetration resolution.
    //    console.log("rp: "+movePerIMass.y * this.particle[0].inverseMass);
    //    console.log("b: "+this.particle[0].position.y);
    this.particle[0].position.x = this.particle[0].position.x + movePerIMass.x * this.particle[0].inverseMass;
    this.particle[0].position.y = this.particle[0].position.y - movePerIMass.y * this.particle[0].inverseMass;
    //    console.log("a: "+this.particle[0].position.y);
    if (this.particle[1])
    {
        this.particle[1].position.x = this.particle[1].position.x - movePerIMass.x * this.particle[1].inverseMass;
        this.particle[1].position.y = this.particle[1].position.y + movePerIMass.y * this.particle[1].inverseMass;
    }
}

/**
* The contact resolution routine for particle contacts. One
* resolver instance can be shared for the whole simulation.
*/
function ParticleContactResolver(iterations)
{
    /**
* Holds the number of iterations allowed.
*/
    this.iterations = iterations;
    /**
* This is a performance tracking value - we keep a record
* of the actual number of iterations used.
*/
    this.iterationsUsed = 0;
}

/**
* Resolves a set of particle contacts for both penetration
* and velocity.
*/
ParticleContactResolver.prototype.resolveContacts = function(contactArray,numContacts,duration){
    this.iterationsUsed = 0;
    var maxIndex = 0;
    while(this.iterationsUsed < this.iterations)
    {
        if (maxIndex == numContacts) break;
        // Resolve this contact.
        contactArray[maxIndex].resolve(duration);
        maxIndex++;
        this.iterationsUsed++;
    }
    contactArray.length = 0;
}

/**
* Links connect two particles together, generating a contact if
* they violate the constraints of their link. It is used as a
* base class for cables and rods, and could be used as a base
* class for springs with a limit to their extension.
*/
function ParticleLink()
{

    /**
* Holds the pair of particles that are connected by this link.
*/
    this.particle = new Array();
}
/**
* Returns the current length of the cable.
*/
ParticleLink.prototype.currentLength = function(){
    var relativePos = new Point(this.particle[0].position.x - this.particle[1].position.x,this.particle[0].position.y - this.particle[1].position.y);
    return relativePos.length;
}

/**
* Fills the given contact structure with the contact needed
* to keep the link from violating its constraint. The contact
* pointer should point to the first available contact in a
* contact array, where limit is the maximum number of
* contacts in the array that can be written to. The method
* returns the number of contacts that have been written. This
* format is common to contact-generating functions, but this
* class can only generate a single contact, so the
* pointer can be a pointer to a single element. The limit
* parameter is assumed to be at least one (zero isn’t valid),
* and the return value is either 0, if the cable wasn’t
* overextended, or one if a contact was needed.
*/
ParticleLink.prototype.fillContact = function(contact,limit){
    return 0;
}
/**
* Cables link a pair of particles, generating a contact if they
* stray too far apart.
*/
function ParticleCable()
{
    ParticleLink.call(this);
    /**
* Holds the maximum length of the cable.
*/
    this.maxLength = null;
    /**
* Holds the restitution (bounciness) of the cable.
*/
    this.restitution = null;
    this.path = null;
}
ParticleCable.prototype = new ParticleLink();
ParticleCable.prototype.constructor = ParticleCable;
/**
* Fills the given contact structure with the contact needed
* to keep the cable from overextending.
*/
ParticleCable.prototype.fillContact = function(contact, limit){
    this.path.segments[0].point = this.particle[0].position;
    this.path.segments[2].point = this.particle[1].position;
    this.path.smooth();
    // Find the length of the cable.
    var length = this.currentLength();
    // Check whether we’re overextended.
    if (length < this.maxLength)
    {
        var vector = new Point(this.path.segments[0].point.x-this.path.segments[1].point.x,this.path.segments[0].point.y-this.path.segments[1].point.y);
        vector.length = this.maxLength/2;
        this.path.segments[1].point.x = this.particle[1].position.x + vector.x;
        this.path.segments[1].point.y = this.particle[1].position.y + vector.y;
        return 0;
    }
    this.path.segments[1].point.x = this.particle[0].position.x + (this.particle[1].position.x - this.particle[0].position.x)/2;
    this.path.segments[1].point.y = this.particle[0].position.y + (this.particle[1].position.y - this.particle[0].position.y)/2;
    // Otherwise return the contact.
    var genContact = new ParticleContact();
    contact.push(genContact);
    genContact.particle[0] = this.particle[0];
    genContact.particle[1] = this.particle[1];
    // Calculate the normal.
    var normal = new Point(this.particle[1].position.x - this.particle[0].position.x,this.particle[1].position.y - this.particle[0].position.y);
    normal = normal.normalize();
    genContact.contactNormal = normal;
    genContact.penetration = length-this.maxLength;
    genContact.restitution = this.restitution;
    return 1;
}
/**
* Rods link a pair of particles, generating a contact if they
* stray too far apart or too close.
*/
function ParticleRod()
{
    ParticleLink.call(this);
    /**
* Holds the length of the rod.
*/
    this.length = null;
    this.path = null;

}

ParticleRod.prototype = new ParticleLink();
ParticleRod.prototype.constructor = ParticleRod;
/**
* Fills the given contact structure with the contact needed
* to keep the rod from extending or compressing.
*/
ParticleRod.prototype.fillContact = function(contact,limit){
    // Find the length of the rod.
    var currentLen = this.currentLength();
    // Check whether we’re overextended.
    if (currentLen == this.length)
    {
        return 0;
    }
    this.path.segments[0].point = this.particle[0].position;
    this.path.segments[1].point = this.particle[1].position;
    var genContact = new ParticleContact();
    var genContact2 = new ParticleContact();
    contact.push(genContact);
    // Otherwise return the contact.
    genContact.particle[0] = this.particle[0];
    genContact.particle[1] = this.particle[1];
    // Calculate the normal.
    var normal = new Point(this.particle[1].position.x - this.particle[0].position.x,this.particle[1].position.y - this.particle[0].position.y);
    normal = normal.normalize();
    // The contact normal depends on whether we’re extending
    // or compressing.
    if (currentLen > this.length) {
        genContact.contactNormal = normal;
        genContact.penetration = currentLen - this.length;
    } else {
        genContact.contactNormal = new Point(normal.x * -1,normal.y *-1);
        genContact.penetration = this.length - currentLen;
    }
    // Always use zero restitution (no bounciness).
    console.log("current len:" + currentLen);
    console.log("pene" + genContact.penetration);
    if(genContact.penetration>100){
        gameOver = gameOver;
    }
    genContact.restitution = 0;
    return 1;
}
/**
* Holds one particle in the linked list of particles.
*/
function ParticleRegistration()
{
    this.particle = null;
    this.next = null;
}
/**
* Holds one registered contact generator.
*/
function ContactGenRegistration()
{
    //of type ParticleContactGenerator
    this.gen = null;
    //of type ContactGenRegistration
    this.next = null;
}
/**
* Keeps track of a set of particles, and provides the means to
* update them all.
*/
/**
* Creates a new particle simulator that can handle up to the
* given number of contacts per frame. You can also optionally
* give a number of contact-resolution iterations to use. If you
* don’t give a number of iterations, then twice the number of
* contacts will be used.
*/
function ParticleWorld(maxContacts,iterations)
{
    /**
    * Holds the list of registrations.
    */
    //of type ParticleRegistration
    this.firstParticle = null;
    /**
    * True if the world should calculate the number of iterations
    * to give the contact resolver at each frame.
    */
    this.calculateIterations = (iterations==0);
    /**
    * Holds the force generators for the particles in this world.
    */
    //of type ParticleForceRegistry
    this.registry = null;
    /**
* Holds the resolver for contacts.
*/
    //of type ParticleContactResolver
    this.resolver = new ParticleContactResolver(iterations);
    /**
* Holds the list of contact generators.
*/
    //of type ContactGenRegistration
    this.firstContactGen = null;
    /**
* Holds the list of contacts.
*/
    //array of type ParticleContact
    this.contacts = new Array();
    /**
* Holds the maximum number of contacts allowed (i.e., the
* size of the contacts array).
*/
    this.maxContacts = maxContacts;
}
/**
* Initializes the world for a simulation frame. This clears
* the force accumulators for particles in the world. After
* calling this, the particles can have their forces for this
* frame added.
*/
ParticleWorld.prototype.startFrame = function(){
    var reg = this.firstParticle;
    while (reg)
    {
        // Remove all forces from the accumulator.
        reg.particle.forceAccum.x = 0;
        reg.particle.forceAccum.y = 0;
        // Get the next registration.
        reg = reg.next;
    }
}
/**
* Calls each of the registered contact generators to report
* their contacts. Returns the number of generated contacts.
*/
ParticleWorld.prototype.generateContacts = function(){
    var limit = this.maxContacts;
    //of Type ParticleContact
    var contactIndex = 0;
    var nextContact = this.contacts;
    var reg = this.firstContactGen;
    while (reg)
    {
        var used = reg.gen.fillContact(nextContact, limit);
        limit -= used;
        contactIndex += used;
        //nextContact += used;
        // We’ve run out of contacts to fill. This means we’re missing
        // contacts.
        if (limit <= 0) break;
        reg = reg.next;
    }
    // Return the number of contacts used.
    return this.maxContacts - limit;
}
/**
* Integrates all the particles in this world forward in time
* by the given duration.
*/
ParticleWorld.prototype.integrate = function(duration){
    var reg = this.firstParticle;
    while (reg)
    {
        // Remove all forces from the accumulator.
        reg.particle.integrate(duration);
        // Get the next registration.
        reg = reg.next;
    }    
}
/**
* Processes all the physics for the particle world.
*/
ParticleWorld.prototype.runPhysics = function(duration){
    // First apply the force generators.
    this.registry.updateForces(duration);
    // Then integrate the objects.
    this.integrate(duration);
    // Generate contacts.
    var usedContacts = this.generateContacts();
    //    console.log(usedContacts);
    //    // And process them.
    if (this.calculateIterations) this.resolver.iterations = usedContacts * 2;
    this.resolver.resolveContacts(this.contacts, usedContacts, duration);
}


/**
* This is the basic polymorphic interface for contact generators
* applying to particles.
*/
function ParticleContactGenerator()
{
//    this.frameContact
}
/**
* Fills the given contact structure with the generated
* contact. The contact pointer should point to the first
* available contact in a contact array, where limit is the
* maximum number of contacts in the array that can be written
* to. The method returns the number of contacts that have
* been written.
*/
ParticleContactGenerator.prototype.fillContact = function(contact,limit){
    
    }

function BoundryContactGenerator(restitution){
    this.restitution = restitution;
    this.particles = new Array();
}

BoundryContactGenerator.prototype.fillContact = function(contact,limit){
    var usedContacts = 0;
    for(var i=0;i<this.particles.length;i++){
        if(this.particles[i].bindedShape.bounds.bottom>view.size.height){
            var genContact = new ParticleContact();
            genContact.particle.push(this.particles[i]);
            genContact.contactNormal = new Point(0,-1);
            genContact.penetration = this.particles[i].bindedShape.bounds.bottom - view.size.height;
            genContact.restitution = this.restitution;
            contact.push(genContact);
            console.log(genContact);
            usedContacts++;
        }
        if(this.particles[i].bindedShape.bounds.top<0){
            var genContact2 = new ParticleContact();
            genContact2.particle.push(this.particles[i]);
            genContact2.contactNormal = new Point(0,1);
            genContact2.penetration = -this.particles[i].bindedShape.bounds.top;
            genContact2.restitution = 1;
            contact.push(genContact2);
            console.log(genContact);
            usedContacts++;
        }
        if(this.particles[i].bindedShape.bounds.right>view.size.width){
            var genContact3 = new ParticleContact();
            genContact3.particle.push(this.particles[i]);
            genContact3.contactNormal = new Point(-1,0);
            genContact3.penetration = this.particles[i].bindedShape.bounds.right - view.size.width;
            genContact3.restitution = 1;
            contact.push(genContact3);
            console.log(genContact);
            usedContacts++;
        }
        if(this.particles[i].bindedShape.bounds.left<0){
            var genContact4 = new ParticleContact();
            genContact4.particle.push(this.particles[i]);
            genContact4.contactNormal = new Point(1,0);
            genContact4.penetration = -this.particles[i].bindedShape.bounds.left;
            genContact4.restitution = 1;
            contact.push(genContact4);
            console.log(genContact);
            usedContacts++;
        }
    }
    return usedContacts;
}
function CirclesContactGenerator(restitution){
    this.restitution = restitution;
    this.particles = new Array();
}

CirclesContactGenerator.prototype.fillContact = function(contact,limit){
    var usedContacts = 0;
    for(var i=0;i<this.particles.length;i++){
        for(var j=i+1;j<this.particles.length;j++){
            //            if(Math.abs(this.particles[i].position.x-this.particles[j].position.x)<= this.particles[i].radius + this.particles[j].radius&& Math.abs(this.particles[i].position.y-this.particles[j].position.y)<=this.particles[i].radius + this.particles[j].radius){
            //                var vector = null;
            //                var genContact = new ParticleContact();
            //                genContact.particle.push(this.particles[i],this.particles[j]);
            //                if(Math.abs(this.particles[i].position.x-this.particles[j].position.x)<= this.particles[i].radius + this.particles[j].radius){
            //                    vector = new Point(this.particles[i].position.x-this.particles[j].position.x,0);
            //                }else{
            //                    vector = new Point(0,this.particles[i].position.y-this.particles[j].position.y);
            //                }
            //                genContact.contactNormal = vector.normalize();
            //                genContact.penetration = (this.particles[i].radius+this.particles[j].radius) -vector.length;
            //                                console.log(genContact.penetration);
            //                                console.log("normal: " +vector.normalize() );
            //                genContact.restitution = this.restitution;
            //                contact.push(genContact);
            //                usedContacts++;
            //            }
            var vector = new Point(this.particles[i].position.x-this.particles[j].position.x,this.particles[i].position.y-this.particles[j].position.y);
            if(vector.length<this.particles[i].radius+this.particles[j].radius){
                //                var helperPath = new Path(this.particles[j].position,new Point(this.particles[j].position.x+vector.x,this.particles[j].position.y+vector.y));
                //                helperPath.strokeColor = 'red';
                //                var helperPath2 = new Path(this.particles[i].position,this.particles[j].position);
                //                helperPath2.strokeColor = 'blue';
                var genContact = new ParticleContact();
                genContact.particle.push(this.particles[i],this.particles[j]);
                genContact.contactNormal = vector.normalize();
                genContact.penetration = this.particles[i].radius+this.particles[j].radius-vector.length;
                genContact.restitution = this.restitution;
                contact.push(genContact);
                console.log(genContact);
                usedContacts++;
            }
        }
    }
    return usedContacts;
}
//function Firework(){
//    Particle.call(this);
//    /** Fireworks have an integer type, used for firework rules. */
//    this.type = null;
//    /**
//     * The age of a firework determines when it detonates. Age gradually
//     * decreases; when it passes zero the firework delivers its payload.
//     * Think of age as fuse-left.
//     */
//    this.age = null;
//}
//Firework.prototype = new Particle();
//Firework.prototype.constructor = Firework;
///**
// * Updates the firework by the given duration of time. Returns true
// * if the firework has reached the end of its life and needs to be
// * removed.
// */
//Firework.prototype.update = function(duration)
//{
//    // Update our physical state
//    this.integrate(duration);
//    // We work backward from our age to zero.
//    this.age -= duration;
//    return (this.age < 0);
//}
//
//
///**
// * Firework rules control the length of a firework’s fuse and the
// * particles it should evolve into.
// */
//function FireworkRule()
//{
//    /** The type of firework that is managed by this rule. */
//    this.type = null;
//    /** The minimum length of the fuse. */
//    this.minAge = null;
//    /** The maximum length of the fuse. */
//    this.maxAge = null;
//    /** The minimum relative velocity of this firework. */
//    this.minVelocity = null;//vector
//    /** The maximum relative velocity of this firework. */
//    this.maxVelocity = null;//vector
//    /** The damping of this firework type. */
//    this.damping = null;
//    
//    /** The number of payloads for this firework type. */
//    this.payloadCount = null;
//    /** The set of payloads. */
//    this.payloads = new Array();
//}
//
///**
// * Creates a new firework of this type and writes it into the given
// * instance. The optional parent firework is used to base position
// * and velocity on.
// */
//FireworkRule.prototype.create = function(parent)
//{
//    var firework = new Firework();
//    firework.type = this.type;
//    firework.age = (this.maxAge-this.minAge)*Math.random()+this.minAge;
//    if (parent!=null){
//        var position = new Point();
//        position.x = parent.position.x;
//        position.y = parent.position.y;
//        firework.position = position;
//        var vel = new Point();
//        vel.x = parent.velocity.x;
//        vel.y = parent.velocity.y;
//        vel.x += (this.maxVelocity.x-this.minVelocity.x)*Math.random()+this.minVelocity.x;
//        //        console.log(vel.x);
//        vel.y += (this.maxVelocity.y-this.minVelocity.y)*Math.random()+this.minVelocity.y;
//        //        console.log(vel.y);
//        firework.velocity = vel;
//    //        console.log(firework.velocity);
//    } else{
//        firework.position = new Point(300*Math.random()+200,650);
//        var vel2 = new Point(0,0);
//        vel2.x += (this.maxVelocity.x-this.minVelocity.x)*Math.random()+this.minVelocity.x;
//        vel2.y += (this.maxVelocity.y-this.minVelocity.y)*Math.random()+this.minVelocity.y;
//        firework.velocity = vel2;
//    }
//    // We use a mass of 1 in all cases (no point having fireworks
//    // with different masses, since they are only under the influence
//    // of gravity).
//    firework.inverseMass = 1;
//    firework.damping = this.damping;
//    firework.acceleration = new Point(0,50);
//    return firework;
//}
///**
// * The payload is the new firework type to create when this
// * firework’s fuse is over.
// */
//function Payload(type,count)
//{
//    /** The type of the new particle to create. */
//    this.type = type;
//    /** The number of particles in this payload. */
//    this.count = count;
//}
//var rules = new Array();
//
//var rule0 = new FireworkRule();
//rule0.payloadCount =2;
//rule0.type =1;
//rule0.minAge = 0.5;
//rule0.maxAge = 1.2;
//rule0.minVelocity = new Point(-100,-680);
//rule0.maxVelocity = new Point(100,-870);
//rule0.damping = 0.15;
//rule0.payloads[0] = new Payload(2,10);
//rule0.payloads[1] = new Payload(3,5);
//
//var rule1 = new FireworkRule();
//rule1.payloadCount =0;
//rule1.type =2;
//rule1.minAge = 1.5;
//rule1.maxAge = 2.5;
//rule1.minVelocity = new Point(-150,150);
//rule1.maxVelocity = new Point(150,-100);
//rule1.damping = 0.3;
//
//var rule2 = new FireworkRule();
//rule2.payloadCount =1;
//rule2.type =3;
//rule2.minAge = 0.5;
//rule2.maxAge = 1.2;
//rule2.minVelocity = new Point(-200,-150);
//rule2.maxVelocity = new Point(200,-270);
//rule2.damping = 0.3;
//rule2.payloads[0] = new Payload(2,9);
//
//rules.push(rule0,rule1,rule2);
//
//function create(type,number,parent)
//{
//    var color = new HsbColor(Math.random() * 360, 1, 1);
//    for(var i = 0;i<number;i++){
//        // Get the rule needed to create this firework.
//        var rule = rules[type-1];
//        // Create the firework.
//        var firework = rule.create(parent);
//        var myCircle = new Path.Circle(firework.position, 2);
//        myCircle.fillColor = color;
//        firework.bindedShape = myCircle;
//        fireworks.push(firework);
//    // Increment the index for the next firework.
//    //nextFirework = (nextFirework + 1) % maxFireworks;
//    }
//}
//
//var fireworks = new Array();
var gameOver = false;
window.onload = function() {
    paper.setup('canvas');
    var tool = new Tool();
    var frame = new Path.Rectangle(new Point(0,0),view.size);
    frame.strokeColor = 'black';
    
    
    var world = new ParticleWorld(1000, 0);
    //    var border = new Path(new Point(0,view.size.height - 250),new Point(view.size.width,view.size.height - 250),new Point(view.size.width,view.size.height),new Point(0,view.size.height));
    //    border.fillColor = '4B5CD7';
    //    var particle = new Particle(0);
    //    particle.position.x = -1;
    //    particle.position.y = -1;
    //    particle.velocity.x = 0;
    //    particle.velocity.y = 0;
    //    particle.damping = 1;
    //    var pr = new ParticleRegistration();
    //    pr.particle = particle;
    //
    //    var pcgen = new BoundryContactGenerator(1);
    //    pcgen.particles.push(particle);
    //    var cgreg = new ContactGenRegistration();
    //    cgreg.gen=pcgen;
    //    
    var ccg = new CirclesContactGenerator(1);
    //    ccg.particles.push(particle);
    var cgreg1 = new ContactGenRegistration();
    cgreg1.gen=ccg;
    world.firstContactGen = cgreg1;
    //    cgreg.next = cgreg1;
    //    
    var pfr = new ParticleForceRegistry();
    //    var pfrn = new ParticleForceRegistration();
    //    pfrn.particle = particle;
    //    pfrn.particleForceGenerator = new ParticleGravity();
    
    //    var pfrn0 = new ParticleForceRegistration();
    //    pfrn0.particle = particle;
    //    var bungeeEnd = new Particle();
    //    bungeeEnd.position.x = 50;
    //    pfrn0.particleForceGenerator = new ParticleDrag();
    //    var path = new Path();
    //    path.add(bungeeEnd.position);
    //    path.add(particle.position);
    //    particle.path = path;
    //    path.strokeColor = 'black';

    //    var pfr00 = new ParticleForceRegistration();
    //    pfr00.particle = particle;
    //    pfr00.particleForceGenerator = new ParticleBuoyancy(20, 1, 250, 1000);
    
    //    pfr.registrations.push(pfrn);
    
    //        var springEnd = new Particle();
    //        springEnd.position.x = view.size.width/2;
    var rods= new Array(); 
    var temp = null;
    var temp2 = cgreg1;
    for(var i=0;i<6;i++){
        oneMore(new Point(50 + i*150,100),-300+Math.random()*600);
    //        var path = new Path();
    //        path.add(springEnd.position);
    //        path.add(particle2.position);
    //        particle2.path = path;
    //        path.strokeColor = 'black';
    //oneMore(new Point(Math.random()*view.size.width,Math.random()*view.size.height));
    }
    function oneMore(point,velx){
        var particle2 = new Particle(30);
        particle2.position.x = point.x;
        particle2.position.y = point.y;
        particle2.bindedShape.fillColor = 'orange';
        particle2.name = 'orange';
        particle2.velocity.x = velx;
//        particle2.velocity.y = -300+Math.random()*600;
        particle2.damping = 0.95;
        particle2.inverseMass = 1/20;
        //        particle2.infiniteMass = true;
        ccg.particles.push(particle2);
        //particle2.bindedShape.fillColor = null;
        //particle2.bindedShape = new Path.Circle(particle2.position,(1.3-random)*50);
        //particle2.bindedShape.fillColor = 'black';
        var pr2 = new ParticleRegistration();
        pr2.particle = particle2;
        if(!world.firstParticle)
            world.firstParticle = pr2;
        if(temp)
            temp.next = pr2;
        temp = pr2;
        
        var particle3 = new Particle(30);
        particle3.position.x = point.x + 60;
        particle3.position.y = point.y;
        particle3.bindedShape.fillColor = 'red';
        particle3.name = 'red';
        //        particle3.velocity.x = -300+Math.random()*600;
        //        particle3.velocity.y = -300+Math.random()*600;
        particle3.damping = 0.95;
        particle3.inverseMass = 1/20;
        ccg.particles.push(particle3);
        var pr3 = new ParticleRegistration();
        pr3.particle = particle3;
        temp.next = pr3;
        temp = pr3;
        //        
        var particle4 = new Particle(30);
        particle4.position.x = point.x;
        particle4.position.y = point.y + 60;
        particle4.bindedShape.fillColor = 'blue';
        particle4.name = 'blue';
        //        particle3.velocity.x = -300+Math.random()*600;
        //        particle3.velocity.y = -300+Math.random()*600;
        particle4.damping = 0.95;
        particle4.inverseMass = 1/20;
        ccg.particles.push(particle4);
        var pr4 = new ParticleRegistration();
        pr4.particle = particle4;
        temp.next = pr4;
        temp = pr4;
        //        
        var particle5 = new Particle(30);
        particle5.position.x = point.x + 60;
        particle5.position.y = point.y + 60;
        particle5.bindedShape.fillColor = 'green';
        particle5.name = 'green';
        //        particle3.velocity.x = -300+Math.random()*600;
        //        particle3.velocity.y = -300+Math.random()*600;
        particle5.damping = 0.95;
        particle5.inverseMass = 1/20;
        ccg.particles.push(particle5);
        var pr5 = new ParticleRegistration();
        pr5.particle = particle5;
        temp.next = pr5;
        temp = pr5;
        
        var particle6 = new Particle(12.5);
        particle6.position.x = point.x + 30;
        particle6.position.y = point.y + 30;
        particle6.bindedShape.fillColor = 'purple';
        particle6.name = 'purple';
        //        particle3.velocity.x = -300+Math.random()*600;
        //        particle3.velocity.y = -300+Math.random()*600;
        particle6.damping = 0.95;
        particle6.inverseMass = 1/20;
        ccg.particles.push(particle6);
        var pr6 = new ParticleRegistration();
        pr6.particle = particle6;
        temp.next = pr6;
        temp = pr6;
        
        var pfrn2 = new ParticleForceRegistration();
        pfrn2.particle = particle3;
        pfrn2.particleForceGenerator = new ParticleGravity();
        
        var pfrn3 = new ParticleForceRegistration();
        pfrn3.particle = particle4;
        pfrn3.particleForceGenerator = new ParticleGravity();
        
        var pfrn5 = new ParticleForceRegistration();
        pfrn5.particle = particle5;
        pfrn5.particleForceGenerator = new ParticleGravity();
        
        var pfrn6 = new ParticleForceRegistration();
        pfrn6.particle = particle2;
        pfrn6.particleForceGenerator = new ParticleGravity();
        
        
        //        var pfrn3 = new ParticleForceRegistration();
        //        pfrn3.particle = particle2;
        //        var springEnd = new Particle();
        //        springEnd.position.x = particle2.position.x;
        //        var pd = new ParticleSpring(springEnd, 4+Math.random()*10, 300);
        //        pfrn3.particleForceGenerator = pd;
        var pfrn4 = new ParticleForceRegistration();
        pfrn4.particle = particle2;
        var pdd = new ParticleDrag();
        pdd.k1 = 10;
        pfrn4.particleForceGenerator = pdd;
        //        var pfr5 = new ParticleForceRegistration();
        //        pfr5.particle = particle2;
        //        pfr5.particleForceGenerator = new ParticleBuoyancy(20, 0.8+Math.random()*0.4, 250, 1000);
        var pcgen1 = new BoundryContactGenerator(0.9);
        pcgen1.particles.push(particle2);
        var cgreg2 = new ContactGenRegistration();
        cgreg2.gen=pcgen1;
        if(temp2)
            temp2.next = cgreg2;
        temp2 = cgreg2;
        
        var pcgen2 = new BoundryContactGenerator(0.9);
        pcgen2.particles.push(particle3);
        var cgreg3 = new ContactGenRegistration();
        cgreg3.gen=pcgen2;
        temp2.next = cgreg3;
        temp2 = cgreg3;
        //        
        var pcgen3 = new BoundryContactGenerator(0.9);
        pcgen3.particles.push(particle4);
        var cgreg5 = new ContactGenRegistration();
        cgreg5.gen=pcgen3;
        temp2.next = cgreg5;
        temp2 = cgreg5;
        //        
        var pcgen4 = new BoundryContactGenerator(0.9);
        pcgen4.particles.push(particle5);
        var cgreg7 = new ContactGenRegistration();
        cgreg7.gen=pcgen4;
        temp2.next = cgreg7;
        temp2 = cgreg7;
        
        var pcgen5 = new BoundryContactGenerator(0.9);
        pcgen5.particles.push(particle5);
        var cgreg9 = new ContactGenRegistration();
        cgreg9.gen=pcgen5;
        temp2.next = cgreg9;
        temp2 = cgreg9;
        
        var rod = new ParticleRod();
        rod.length = 60;
        rod.particle.push(particle2,particle3);
        //        rod.restitution = 0.9;
        rod.path = new Path(particle2.position,particle3.position);
        //        rod.path.strokeColor = 'purple';
        //        rod.path.strokeWidth = 60;
        rod.path.strokeCap = 'round'; 
        var cgreg4 = new ContactGenRegistration();
        cgreg4.gen = rod;
        temp2.next = cgreg4;
        temp2 = cgreg4;
        
        var rod1 = new ParticleRod();
        rod1.length = 60;
        rod1.particle.push(particle2,particle4);
        //        rod.restitution = 0.9;
        rod1.path = new Path(particle2.position,particle4.position);
        //        rod1.path.strokeColor = 'purple';
        //        rod1.path.strokeWidth = 60;
        rod1.path.strokeCap = 'round'; 
        var cgreg6 = new ContactGenRegistration();
        cgreg6.gen = rod1;
        temp2.next = cgreg6;
        temp2 = cgreg6;
        
        var rod2 = new ParticleRod();
        rod2.length = 60;
        rod2.particle.push(particle5,particle4);
        //        rod.restitution = 0.9;
        rod2.path = new Path(particle5.position,particle4.position);
        //        rod2.path.strokeColor = 'purple';
        //        rod2.path.strokeWidth = 60;
        rod2.path.strokeCap = 'round'; 
        var cgreg8 = new ContactGenRegistration();
        cgreg8.gen = rod2;
        temp2.next = cgreg8;
        temp2 = cgreg8;
        
        var rod3 = new ParticleRod();
        rod3.length = 60;
        rod3.particle.push(particle5,particle3);
        //        rod.restitution = 0.9;
        rod3.path = new Path(particle5.position,particle3.position);
        //        rod3.path.strokeColor = 'purple';
        //        rod3.path.strokeWidth = 60;
        rod3.path.strokeCap = 'round'; 
        var cgreg90 = new ContactGenRegistration();
        cgreg90.gen = rod3;
        temp2.next = cgreg90;
        temp2 = cgreg90;
        rods.push(rod,rod1, rod2,rod3);
        pfr.registrations.push(pfrn2,pfrn4,pfrn3,pfrn5,pfrn6);
    }
    function oneMoreTriangle(point,velx){
        var particle2 = new Particle(30);
        particle2.position.x = point.x;
        particle2.position.y = point.y;
        particle2.bindedShape.fillColor = 'orange';
        particle2.name = 'orange';
        particle2.velocity.x = velx;
//        particle2.velocity.y = -300+Math.random()*600;
        particle2.damping = 0.95;
        particle2.inverseMass = 1/20;
        //        particle2.infiniteMass = true;
        ccg.particles.push(particle2);
        //particle2.bindedShape.fillColor = null;
        //particle2.bindedShape = new Path.Circle(particle2.position,(1.3-random)*50);
        //particle2.bindedShape.fillColor = 'black';
        var pr2 = new ParticleRegistration();
        pr2.particle = particle2;
        if(!world.firstParticle)
            world.firstParticle = pr2;
        if(temp)
            temp.next = pr2;
        temp = pr2;
        
        var particle3 = new Particle(30);
        particle3.position.x = point.x + 60;
        particle3.position.y = point.y;
        particle3.bindedShape.fillColor = 'red';
        particle3.name = 'red';
        //        particle3.velocity.x = -300+Math.random()*600;
        //        particle3.velocity.y = -300+Math.random()*600;
        particle3.damping = 0.95;
        particle3.inverseMass = 1/20;
        ccg.particles.push(particle3);
        var pr3 = new ParticleRegistration();
        pr3.particle = particle3;
        temp.next = pr3;
        temp = pr3;
        //        
        var particle4 = new Particle(30);
        particle4.position.x = point.x+30;
        particle4.position.y = point.y + 60;
        particle4.bindedShape.fillColor = 'blue';
        particle4.name = 'blue';
        //        particle3.velocity.x = -300+Math.random()*600;
        //        particle3.velocity.y = -300+Math.random()*600;
        particle4.damping = 0.95;
        particle4.inverseMass = 1/20;
        ccg.particles.push(particle4);
        var pr4 = new ParticleRegistration();
        pr4.particle = particle4;
        temp.next = pr4;
        temp = pr4;
        //        
//        var particle5 = new Particle(30);
//        particle5.position.x = point.x + 60;
//        particle5.position.y = point.y + 60;
//        particle5.bindedShape.fillColor = 'green';
//        particle5.name = 'green';
//        //        particle3.velocity.x = -300+Math.random()*600;
//        //        particle3.velocity.y = -300+Math.random()*600;
//        particle5.damping = 0.95;
//        particle5.inverseMass = 1/20;
//        ccg.particles.push(particle5);
//        var pr5 = new ParticleRegistration();
//        pr5.particle = particle5;
//        temp.next = pr5;
//        temp = pr5;
//        
//        var particle6 = new Particle(12.5);
//        particle6.position.x = point.x + 30;
//        particle6.position.y = point.y + 30;
//        particle6.bindedShape.fillColor = 'purple';
//        particle6.name = 'purple';
//        //        particle3.velocity.x = -300+Math.random()*600;
//        //        particle3.velocity.y = -300+Math.random()*600;
//        particle6.damping = 0.95;
//        particle6.inverseMass = 1/20;
//        ccg.particles.push(particle6);
//        var pr6 = new ParticleRegistration();
//        pr6.particle = particle6;
//        temp.next = pr6;
//        temp = pr6;
        
        var pfrn2 = new ParticleForceRegistration();
        pfrn2.particle = particle3;
        pfrn2.particleForceGenerator = new ParticleGravity();
        
        var pfrn3 = new ParticleForceRegistration();
        pfrn3.particle = particle4;
        pfrn3.particleForceGenerator = new ParticleGravity();
        
//        var pfrn5 = new ParticleForceRegistration();
//        pfrn5.particle = particle5;
//        pfrn5.particleForceGenerator = new ParticleGravity();
        
        var pfrn6 = new ParticleForceRegistration();
        pfrn6.particle = particle2;
        pfrn6.particleForceGenerator = new ParticleGravity();
        
        
        //        var pfrn3 = new ParticleForceRegistration();
        //        pfrn3.particle = particle2;
        //        var springEnd = new Particle();
        //        springEnd.position.x = particle2.position.x;
        //        var pd = new ParticleSpring(springEnd, 4+Math.random()*10, 300);
        //        pfrn3.particleForceGenerator = pd;
        var pfrn4 = new ParticleForceRegistration();
        pfrn4.particle = particle2;
        var pdd = new ParticleDrag();
        pdd.k1 = 10;
        pfrn4.particleForceGenerator = pdd;
        //        var pfr5 = new ParticleForceRegistration();
        //        pfr5.particle = particle2;
        //        pfr5.particleForceGenerator = new ParticleBuoyancy(20, 0.8+Math.random()*0.4, 250, 1000);
        var pcgen1 = new BoundryContactGenerator(0.9);
        pcgen1.particles.push(particle2);
        var cgreg2 = new ContactGenRegistration();
        cgreg2.gen=pcgen1;
        if(temp2)
            temp2.next = cgreg2;
        temp2 = cgreg2;
        
        var pcgen2 = new BoundryContactGenerator(0.9);
        pcgen2.particles.push(particle3);
        var cgreg3 = new ContactGenRegistration();
        cgreg3.gen=pcgen2;
        temp2.next = cgreg3;
        temp2 = cgreg3;
        //        
        var pcgen3 = new BoundryContactGenerator(0.9);
        pcgen3.particles.push(particle4);
        var cgreg5 = new ContactGenRegistration();
        cgreg5.gen=pcgen3;
        temp2.next = cgreg5;
        temp2 = cgreg5;
        //        
//        var pcgen4 = new BoundryContactGenerator(0.9);
//        pcgen4.particles.push(particle5);
//        var cgreg7 = new ContactGenRegistration();
//        cgreg7.gen=pcgen4;
//        temp2.next = cgreg7;
//        temp2 = cgreg7;
//        
//        var pcgen5 = new BoundryContactGenerator(0.9);
//        pcgen5.particles.push(particle5);
//        var cgreg9 = new ContactGenRegistration();
//        cgreg9.gen=pcgen5;
//        temp2.next = cgreg9;
//        temp2 = cgreg9;
        
        var rod = new ParticleRod();
        rod.length = 62;
        rod.particle.push(particle2,particle3);
        //        rod.restitution = 0.9;
        rod.path = new Path(particle2.position,particle3.position);
        //        rod.path.strokeColor = 'purple';
        //        rod.path.strokeWidth = 60;
        rod.path.strokeCap = 'round'; 
        var cgreg4 = new ContactGenRegistration();
        cgreg4.gen = rod;
        temp2.next = cgreg4;
        temp2 = cgreg4;
        
        var rod1 = new ParticleRod();
        rod1.length = 62;
        rod1.particle.push(particle2,particle4);
        //        rod.restitution = 0.9;
        rod1.path = new Path(particle2.position,particle4.position);
        //        rod1.path.strokeColor = 'purple';
        //        rod1.path.strokeWidth = 60;
        rod1.path.strokeCap = 'round'; 
        var cgreg6 = new ContactGenRegistration();
        cgreg6.gen = rod1;
        temp2.next = cgreg6;
        temp2 = cgreg6;
        
        var rod2 = new ParticleRod();
        rod2.length = 62;
        rod2.particle.push(particle3,particle4);
        //        rod.restitution = 0.9;
        rod2.path = new Path(particle3.position,particle4.position);
        //        rod2.path.strokeColor = 'purple';
        //        rod2.path.strokeWidth = 60;
        rod2.path.strokeCap = 'round'; 
        var cgreg8 = new ContactGenRegistration();
        cgreg8.gen = rod2;
        temp2.next = cgreg8;
        temp2 = cgreg8;
        
//        var rod3 = new ParticleRod();
//        rod3.length = 60;
//        rod3.particle.push(particle5,particle3);
//        //        rod.restitution = 0.9;
//        rod3.path = new Path(particle5.position,particle3.position);
//        //        rod3.path.strokeColor = 'purple';
//        //        rod3.path.strokeWidth = 60;
//        rod3.path.strokeCap = 'round'; 
//        var cgreg90 = new ContactGenRegistration();
//        cgreg90.gen = rod3;
//        temp2.next = cgreg90;
//        temp2 = cgreg90;
        rods.push(rod,rod1, rod2);
        pfr.registrations.push(pfrn2,pfrn4,pfrn3,pfrn6);
    }

    
    world.registry = pfr;
    tool.onMouseDown = function(event){
        if(Math.random()<0.5){
            oneMoreTriangle(event.point,0);
        }else{
            oneMore(event.point,0);
        }
    //gameOver = !gameOver;
        
    }
    var b = true;
    tool.onKeyDown = function(event){
        if(event.character=='1'){
            if(b)

            {
                for(var i=0;i<rods.length;i++){
                
                    rods[i].path.strokeColor = 'purple';
                    rods[i].path.strokeWidth = 60;
                        
                }
                b=!b;
            }else{
                for(var i=0;i<rods.length;i++){
                
                    rods[i].path.strokeColor = null;
//                    rods[i].path.strokeWidth = 60;
                        
                }
                b = !b;
            }
        }
    }
    //    console.log(fireworks);
    view.onFrame = function(event){
        if(event.delta>1){
            return;
        }
        if (!gameOver){
            // Prepare the objects for this frame.
            world.startFrame();
            // Update the physics.
            world.runPhysics(event.delta);
        }
    //        for(var i =0 ; i< fireworks.length;i++){
    //            var firework = fireworks[i];
    //                
    //            if (firework.type > 0)
    //            {
    //                // Does it need removing?
    //                //                console.log(i);
    //                //                console.log(firework.velocity);
    //                if (firework.update(event.delta))
    //                {
    //                    var rule = rules[firework.type-1];
    //                    //// Delete the current firework (this doesn’t affect its
    //                    //// position and velocity for passing to the create function,
    //                    //// just whether or not it is processed for rendering or
    //                    //// physics.
    //                    firework.type = 0;
    //                    firework.bindedShape.remove();
    //                    var index = fireworks.indexOf(firework);
    //                    fireworks.splice(index, 1);
    //                    // Add the payload.
    //                    for (var j = 0; j < rule.payloadCount; j++)
    //                    {
    //                        var payload = rule.payloads[j];
    //                        create(payload.type, payload.count, firework);
    //                    }
    //                //}
    //                //}
    //                //}
    //                    
    //                }
    //                
    //                
    //            }
    //            
    //        }
    }
    
    view.draw();
}
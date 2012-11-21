// origin is a vertex that is always defined

@Pretty
geom Tank {
    // Generate two vertices on either side of the origin, using
    // the y axis to define their points
    frontLeft, frontRight = split(origin, Y, 50)

    cuboid "chassis" {
        width: 100
        height: 75
        depth: 200
    }
    // Anchor this cuboid using the two vertices specified
    // above. Note that these vertices, and the nature of the
    // cuboid, means the width specified is redundant. As a result,
    // this value could likely be omitted.
    chassis.frontLeft = frontLeft
    chassis.frontRight = frontRight

    // We can retrieve vertices from the cuboid to create
    // new vertices, which we can use as anchors later on.
    gunPivot = base.topFace.center

    @Cheap
    cylinder "gunBase" {
        radius: 15
        height: 10
    }
    // We specify the location of some geometry by anchoring it.
    // However, we can anchor it using many different ways. The
    // engine will fill in the gaps assuming we've provided sufficient
    // anchors.
    gunBase.bottom.center = gunPivot

    cylinder "gun" {
        radius: 2

        // The properties used to define the gun can also vary. Specifying a
        // cylinder's height will cause the cylinder like a can on a table.
        // Specifying the length, as is done here, causes it to be oriented
        // on its side.
        length: 75
    }

    gun.bottom.center = gunPivot
}

# Builder Pattern{#builder_pattern}

A Builder pattern describes the process of instantiating all the parts of
a complex system starting with a Director.  The Director is responsible for
instantiating all the parts of the system.  The intent is to separate the
data portion (as represented by the Director) from the presentation of the
data (as represented a Builder that knows how to build each part of the
presentation.  The closest analogy I can think of for the Builder pattern
is the Model-View-Controller (MVC) design, where the Model holds the data,
the View presents the data in one or more formats (views created by the
Builder), and the Controller (Director) works with the user, the Model, and
the View to present the data to the user.

## How to Use

I did not write any examples of a Builder design pattern.

### See Also
- @ref mainpage "Main page"

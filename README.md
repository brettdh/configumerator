# Configumerator

Yet another configuration file assistance library.

## Why?

All the libraries I found seemed to be overkill for the simple uses
that I needed. Plus, I wanted something that could easily work on
both Android and non-Android Linux.

## Okay, but why do I care?

You have a lot of questions for someone I've never met.

You might care if you want a simple library that converts a configuration file
into a C++ class that you can then query for that configuration file's content.
You might also enjoy not re-writing the same option validation code in different
projects. I certainly enjoyed it.

## Fine, so how do I use it?

Absolutely chuffed you asked! It goes a-litle something like this. First you
install it:

### Android

    $ cd $NDK_MODULE_PATH
    $ mkdir edu.umich.mobility
    $ git clone https://github.com/brettdh/configumerator.git

then add this line to the end of your `Android.mk`:

    $(call import-module, edu.umich.mobility/configumerator)

Don't forget to add `configumerator` to your `LOCAL_SHARED_LIBRARIES`.

### Not-Android

    $ git clone https://github.com/brettdh/configumerator.git
    $ cd configumerator
    $ make
    $ sudo make install

And then you use it!  Like so:

    #include <configumerator.h>

Then, define a subclass of `configumerator::Config` that defines a `setup`
method. This method should call some of these functions to register the names
of different config options of different types:

    registerBooleanOption
    registerStringOption
    registerDoubleOption
    registerDoubleListOption

Each of these reads what it says it reads; a list of double-precision floats
is delimited by spaces.

Additionally, there's `registerOptionReader`, which takes an option-reading
function and a pointer to a set of option keys and arranges to call the reader
function whenever a line in the config file matches one of the keys. The
function receives two arguments -- the key and the rest of the line,
as strings -- and returns nothing. It should accomplish the option-saving by
modifying the `Config` subclass.  For instance, the above `register*`
methods are implemented using `std::bind` and a member function.

You probably also want to define some public accessor methods for the options
you're reading in.

Speaking of reading in: you'll need to define a static method that returns
an instance of your `Config` subclass.  Your constructor will need to create
a `Config` instance and call `loadConfig(filename)` on it. This will cause a
few things to happen:

* Your `setup` method will be called
* The file will be read
* Your `validate` method will be called

If configumerator encounters any errors when reading the file -- for example,
an option that doesn't match any that you've registered, or a numeric option
that can't be parsed as a number -- it will throw a `ConfigValidationError`.
If you need any special validation steps, implement them in `validate` and
throw the same error. If an error occurs, `loadConfig` will catch the exception,
print a message about the error, and then exit.

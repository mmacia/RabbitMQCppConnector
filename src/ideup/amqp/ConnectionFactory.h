
#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <string>

/**
  * class ConnectionFactory
  * 
  */

class ConnectionFactory
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  ConnectionFactory ( );

  /**
   * Empty Destructor
   */
  virtual ~ConnectionFactory ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @return Connection
   * @param  host
   * @param  port
   * @param  user
   * @param  pass
   * @param  vhost
   */
  static Connection newConnection (string host = localhost, int port = 5672, string user = guest, string pass = guest, string vhost = / )
  {
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:



};

#endif // CONNECTIONFACTORY_H

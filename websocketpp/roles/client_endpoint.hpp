/*
 * Copyright (c) 2013, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef WEBSOCKETPP_CLIENT_ENDPOINT_HPP
#define WEBSOCKETPP_CLIENT_ENDPOINT_HPP

#include <websocketpp/endpoint.hpp>
#include <websocketpp/logger/levels.hpp>

#include <iostream>

namespace websocketpp {


/// Client endpoint role based on the given config
/**
 *
 */
template <typename config>
class client : public endpoint<connection<config>,config> {
public:
    /// Type of this endpoint
	typedef client<config> type;	
	
	/// Type of the endpoint concurrency component
	typedef typename config::concurrency_type concurrency_type;
    /// Type of the endpoint transport component
	typedef typename config::transport_type transport_type;
	
	/// Type of the connections this server will create
	typedef connection<config> connection_type;
	/// Type of a shared pointer to the connections this server will create
    typedef typename connection_type::ptr connection_ptr;

    /// Type of the connection transport component
    typedef typename transport_type::transport_con_type transport_con_type;
    /// Type of a shared pointer to the connection transport component
    typedef typename transport_con_type::ptr transport_con_ptr;

	/// Type of the endpoint component of this server
	typedef endpoint<connection_type,config> endpoint_type;
	
	explicit client() : endpoint_type(false)
	{
		endpoint_type::m_alog.write(log::alevel::devel,
            "client constructor");
	}
	
	/// Get a new connection
	/**
	 * Creates and returns a pointer to a new connection to the given URI
	 * suitable for passing to connect(connection_ptr). This method allows
	 * applying connection specific settings before performing the opening
	 * handshake.
	 * 
	 * @return A connection_ptr to the new connection
	 */
	connection_ptr get_connection(const std::string& u, lib::error_code &ec) {
	    // parse uri
        try {
            // uri validation
            uri_ptr location(new uri(u));
            
            if (location->get_secure() && !transport_type::is_secure()) {
                ec = error::make_error_code(error::endpoint_not_secure);
                return connection_ptr();
            }
            
            // create connection
            connection_ptr con = endpoint_type::create_connection();
            
            if (!con) {
                ec = error::make_error_code(error::con_creation_failed);
                return con;
            }
            
            // Success
            ec = lib::error_code();
            return con;
        } catch (uri_exception) {
            ec = error::make_error_code(error::invalid_uri);
            return connection_ptr();
        }
	}
	
	/// Begin the connection process for the given connection
	/**
	 * Initiates the opening connection handshake for connection con. Exact
	 * behavior depends on the underlying transport policy.
	 *
	 * @return The pointer to the connection originally passed in.
	 */
	connection_ptr connect(connection_ptr con) {
	    // transport async_connect
	    
	    return con;
	}
	
	
	
	// connect(...)
private:
    // handle_connect
    void handle_connect(connection_ptr con, const lib::error_code & ec) {
        // start connection if successful
        // set failure information if not and call con->terminate
    }
};

} // namespace websocketpp

#endif //WEBSOCKETPP_CLIENT_ENDPOINT_HPP
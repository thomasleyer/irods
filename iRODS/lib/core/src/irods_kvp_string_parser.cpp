


// =-=-=-=-=-=-=-
#include "irods_kvp_string_parser.hpp"

// =-=-=-=-=-=-=-
// rods includes
#include "rodsErrorTable.hpp"

namespace irods {
    /// =-=-=-=-=-=-=-
    /// @brief function to return defined delimiter
    std::string kvp_delimiter() {
        return KVP_DEF_DELIM;
    }
 
    /// =-=-=-=-=-=-=-
    /// @brief function to return defined delimiter
    std::string kvp_association() {
        return KVP_DEF_ASSOC;
    }

    /// =-=-=-=-=-=-=-
    /// @brief given a string, break the string along the kvp association and then
    ///        place the pair into the map
    static
    error parse_token_into_kvp(
        const std::string& _token,
        kvp_map_t&         _kvp,
        const std::string& _assoc ) {
        // =-=-=-=-=-=-=-
        // split along the associative delimiter and place into the map
        std::vector< std::string > token_vec;
        boost::split( token_vec, _token, boost::is_any_of( _assoc ), boost::token_compress_on );
        if( token_vec.size() != 2 ) {
            std::stringstream msg;
            msg << "token vector size != 2 during parsing of ["
                << _token
                << "]";
             return ERROR( 
                        SYS_INVALID_INPUT_PARAM, 
                        msg.str() );
        }

        _kvp[ token_vec[0] ] = token_vec[1];
    
        return SUCCESS();
        
    } // parse_token_into_kvp

    /// =-=-=-=-=-=-=-
    /// @brief given a string, break the string along the delimiter and then
    ///        break the tokens along the assignment for key-value pairs
    error parse_kvp_string( 
        const std::string& _string,
        kvp_map_t&         _kvp,
        const std::string& _assoc,
        const std::string& _delim ) {
        // =-=-=-=-=-=-=-
        // test for the delim first, if there is none then
        // short circuit, test for association and place in map
        size_t pos = _string.find( KVP_DEF_DELIM );
        if( std::string::npos == pos ) {
            // =-=-=-=-=-=-=-
            // no delim, look for association
            pos = _string.find( KVP_DEF_ASSOC );
            if( std::string::npos == pos ) {
                // =-=-=-=-=-=-=-
                // no association, just add to the map
                _kvp[ _string ] = _string;
                return SUCCESS();

            } else {
                // =-=-=-=-=-=-=-
                // association found, break it into a kvp 
                // and place it in the map
                return parse_token_into_kvp( 
                                _string,
                                _kvp,
                                _assoc );
            }

        } // if no delim found

        // =-=-=-=-=-=-=-
        // otherwise parse the string into tokens split by the delimiter
        std::list< std::string > token_list;;
        boost::split( token_list, _string, boost::is_any_of( KVP_DEF_DELIM ), boost::token_compress_on );
        BOOST_FOREACH( std::string& token, token_list ) {
            // =-=-=-=-=-=-=-
            // now that the string is broken into tokens we need to
            // extract the key and value to put them into the map
            error ret = parse_token_into_kvp( 
                            token,
                            _kvp,
                            _assoc );
        }
        
        return SUCCESS();

    } // parse_kvp_string

}; // namespace irods



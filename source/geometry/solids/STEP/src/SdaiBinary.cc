

//



//
// $Id: SdaiBinary.cc,v 1.3 1999-12-15 14:50:17 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

/*
* NIST STEP Core Class Library
* clstepcore/SdaiBinary.cc
* May 1995
* David Sauder

* Development of this software was funded by the United States Government,
* and is not subject to copyright.
*/

/* $Id: SdaiBinary.cc,v */

#include <SdaiBinary.h>

extern Severity 
CheckRemainingInput(G4std::istream &in, ErrorDescriptor *err, 
		    const char *typeName, // used in error message
		    const char *tokenList); // e.g. ",)"

void 
SdaiBinary::STEPwrite (G4std::ostream& out) const
{
    const char *str = 0;
    if (is_null ())
	out << "$";
    else
    {
	out << '\"';
	str = chars ();
	while (*str)
	{
	    out << *str;
	    str++;
	}
	out << '\"';
    }
}

const char * 
SdaiBinary::STEPwrite (SCLstring &s) const
{
    const char *str = 0;
    if (is_null ())
    {
//	s.set_null(); // this would free up space? nope
	s = "$";
    }
    else
    {
	s = "\"";
	str = chars ();
	while (*str)
	{
	    s.Append(*str);
	    str++;
	}
	s.Append(BINARY_DELIM);
    }
    return s.chars();
}

Severity 
SdaiBinary::ReadBinary(G4std::istream& in, ErrorDescriptor *err, int AssignVal,
		       int needDelims)
{
    if(AssignVal)
	set_null();

    SCLstring str;
    char c;
    char messageBuf[512];
    messageBuf[0] = '\0';

    int validDelimiters = 1;

    in >> G4std::ws; // skip white space

    if( in.good() )
    {
	in.get(c);
	if( (c == '\"') || isxdigit(c) )
	{
	    if( c == '\"' )
	    {
		in.get(c); // push past the delimiter
		// since found a valid delimiter it is now invalid until the 
		//   matching ending delim is found
		validDelimiters = 0;
	    }
	    while(in.good() && isxdigit(c))
	    {
		str.Append(c);
		in.get(c);
	    }
	    if(in.good() && (c != '\"') )
		in.putback(c);
	    if( AssignVal && (str.Length() > 0) )
		operator= (str.chars());

	    if(c == '\"') // if found ending delimiter
	    {
		// if expecting delim (i.e. validDelimiter == 0)
		if(!validDelimiters) 
		{
		    validDelimiters = 1; // everything is fine
		}
		else // found ending delimiter but no initial delimiter
		{
		    validDelimiters = 0;
		}
	    }
	    // didn't find any delimiters at all and need them.
	    else if(needDelims) 
	    {
		validDelimiters = 0;
	    }

	    if (!validDelimiters)
	    {	
		err->GreaterSeverity(SEVERITY_WARNING);
		if(needDelims)
		    sprintf(messageBuf, 
			    "Binary value missing double quote delimiters.\n");
		else
		    sprintf(messageBuf, 
			   "Mismatched double quote delimiters for binary.\n");
		err->AppendToDetailMsg(messageBuf);
		err->AppendToUserMsg(messageBuf);
	    }
/*
	    else if ( !isspace(b[0]) && (b[0] != '\0') )
	    {	
		err->GreaterSeverity(SEVERITY_WARNING);
		sprintf(messageBuf, "Invalid binary value.\n");
		err->AppendToDetailMsg(messageBuf);
	    }
*/
	}
	else
	{
	    err->GreaterSeverity(SEVERITY_WARNING);
	    sprintf(messageBuf, "Invalid binary value.\n");
	    err->AppendToDetailMsg(messageBuf);
	    err->AppendToUserMsg(messageBuf);
	}
    }
    else
    {
	err->GreaterSeverity(SEVERITY_INCOMPLETE);
    }
    return err->severity();
}

Severity
SdaiBinary::StrToVal (const char * s, ErrorDescriptor *err)
{
    G4std::istrstream in ((char *)s); // sz defaults to length of s
    return ReadBinary(in, err, 1, 0);
}

/*
    operator= (s);
    if (! strcmp (chars (),  s))  return SEVERITY_NULL ; 
    else return SEVERITY_INPUT_ERROR; 
*/
/////////////////////////////////////////////////
#ifdef bpzdofbqlvzbfxck
    set_null();

    char messageBuf[BUFSIZ];
    messageBuf[0] = '\0';

    int validDelimiters = 1;
    char *start = 0;

    char *b = s;
    while( *b && isspace(*b) )
	b++;

    if( *b )
    {
	if( (b[0] == '\"') || isxdigit(b[0]) )
	{
	    if( b[0] == '\"' )
	    {
		b++; // push past the delimiter
		// since found a valid delimiter it is now invalid until the 
		//   matching ending delim is found
		validDelimiters = 0;
	    }
	    if(isxdigit(b[0]))
		start = b;
	    while(isxdigit(b[0]))
	    {
		b++;
	    }

	    if(b[0] == '\"') // if found ending delimiter
	    {
		// if expecting delim (i.e. validDelimiter == 0)
		if(!validDelimiters) 
		{
		    validDelimiters = 1; // everything is fine
		    b++; // push past closing quote
		}
		else // found ending delimiter but no initial delimiter
		{
		    validDelimiters = 0;
		}
	    }
	    // didn't find any delimiters at all and need them.
	    else if(NeedDelims) 
	    {
		validDelimiters = 0;
	    }

	    if (!validDelimiters)
	    {	
		err->GreaterSeverity(SEVERITY_WARNING);
		sprintf(messageBuf, 
			"Binary value missing double quote delimiters. \n");
	    }
	    else if ( !isspace(b[0]) && (b[0] != '\0') )
	    {	
		err->GreaterSeverity(SEVERITY_WARNING);
		sprintf(messageBuf, "Invalid binary value.\n");
		err->AppendToDetailMsg(messageBuf);
	    }
	}
	else
	{
	    err->GreaterSeverity(SEVERITY_WARNING);
	    sprintf(messageBuf, "Invalid binary value.\n");
	    err->AppendToDetailMsg(messageBuf);
	}
    }
    else
    {
	err->GreaterSeverity(SEVERITY_INCOMPLETE);
    }
    return b;
#endif

//  STEPread reads a binary in exchange file format
//  delimited by double quotes

Severity 
SdaiBinary::STEPread (G4std::istream& in, ErrorDescriptor *err)
{
    return ReadBinary(in, err, 1, 1);
/*
    int foundEndQuote = 0; // need so this string is not ok: 'hi''
    set_null ();  // clear the old string
    char c;
    in >> G4std::ws; // skip white space
    in >> c;

	// remember the current format state to restore the previous settings
    long int flags = in.flags();
    in.unsetf(G4std::ios::skipws);

    if (c == BINARY_DELIM)
    {
	while( in.good() && in.get(c) && (c != BINARY_DELIM) )
	{
	    Append (c);
	}
	Append ('\0');

	if(c == BINARY_DELIM)
	    return SEVERITY_NULL;
	else
	{    // non-recoverable error
	    err->AppendToDetailMsg("Missing closing quote on binary value.\n");
	    err->AppendToUserMsg("Missing closing quote on binary value.\n");
	    err->GreaterSeverity(SEVERITY_INPUT_ERROR);
	    return SEVERITY_INPUT_ERROR;
	}
    }
    //  otherwise there was not a quote
    in.putback (c);
    in.flags(flags); // set the format state back to previous settings

    return err -> GreaterSeverity (SEVERITY_INCOMPLETE);  
*/
}

Severity 
SdaiBinary::STEPread (const char *s, ErrorDescriptor *err)
{
    G4std::istrstream in((char *)s);
    return STEPread (in, err);
}

///////////////////////////////////////////////////////////////////////////////
// * attrValue is validated.
// * err is set if there is an error
// * If optional is 1 then a missing value will be valid otherwise severity
//   incomplete will be set.
// * If you don\'t know if the value may be optional then set it false and 
//   check to see if SEVERITY_INCOMPLETE is set. You can change it later to
//   SEVERITY_NULL if it is valid for the value to be missing.  No error 
//   'message' will be associated with the value being missing so you won\'t 
//   have to worry about undoing an error message.
// * tokenList contains characters that Terminate the expected value.
// * If tokenList is not zero then the value is expected to Terminate before 
//   a character found in tokenlist.  All values read up to the 
//   terminating character (delimiter) must be valid or err will be set with an
//   appropriate error message.  White space between the value and the 
//   terminating character is not considered to be invalid.  If tokenList is 
//   null then attrValue must only contain a valid value and nothing else 
//   following.
///////////////////////////////////////////////////////////////////////////////

Severity 
SdaiBinary::BinaryValidLevel (G4std::istream &in, ErrorDescriptor *err,
				int optional, char *tokenList, 
				int needDelims, int clearError)
{
    if(clearError)
	err->ClearErrorMsg();

    in >> G4std::ws; // skip white space
    char c = in.peek();
    if(c == '$' || in.eof())
    {
	if(!optional)
	    err->GreaterSeverity(SEVERITY_INCOMPLETE);
	if(in)
	    in >> c;
	CheckRemainingInput(in, err, "binary", tokenList);
	return err->severity();
    }
    else
    {
	ErrorDescriptor error;
	ReadBinary(in, &error, 0, needDelims);
	CheckRemainingInput(in, &error, "binary", tokenList);

	Severity sev = error.severity();
	if(sev < SEVERITY_INCOMPLETE)
	{
	    err->AppendToDetailMsg(error.DetailMsg());
	    err->AppendToUserMsg(error.UserMsg());
	    err->GreaterSeverity(error.severity());
	}
	else if(sev == SEVERITY_INCOMPLETE && !optional)
	    err->GreaterSeverity(SEVERITY_INCOMPLETE);
    }
    return err->severity();
}

Severity 
SdaiBinary::BinaryValidLevel (const char *value, ErrorDescriptor *err,
				int optional, char *tokenList, 
				int needDelims, int clearError)
{
    G4std::istrstream in((char *)value);
    return BinaryValidLevel (in, err, optional, tokenList, 
			     needDelims, clearError);
}

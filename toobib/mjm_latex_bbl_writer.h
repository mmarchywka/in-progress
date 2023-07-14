#ifndef MJM_LATEX_BBL_WRITER_H__
#define MJM_LATEX_BBL_WRITER_H__

#include "mjm_globals.h"
#include "mjm_thread_util.h"

#include "mjm_thread_util.h"
#include "mjm_bibtex_entry.h"
#include "mjm_bibitem_entry.h"
#include "mjm_bibtex_fields.h"
#include "mjm_latex_aux_parse.h"
#include "mjm_idiosyncratic_source_locator.h"
#include <map> 
#include <vector> 
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <string>
#include <fstream>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>

/*
2022-07-28 seems to use url's ok but not pick unique well or label accuratel.
Date and authnors need to be formatted consistently. Add orcid ID or more
info to attribution query string. 

*/

// Wed Feb 16 08:03:01 EST 2022
// generated by /home/documents/cpp/scripts/cpputil -classhdr mjm_latex_bbl_writer   
// g++  -Wall -std=gnu++11 -DTEST_MJM_LATEX_BBL_WRITER -I. -I../../mjm/hlib -I../../mjm/num  -gdwarf-3 -O0  -x c++ mjm_latex_bbl_writer.h  -lpthread -lreadline

/*

A typical bbl file entry. Entries can be extracted from the aux file
and produced similarly without the bst file. 

\bibitem{MitochondriaContributeNADPHLeopoldAdlerChunhe2014}
Leopold Adler, Chunhe Chen, and Yiannis Koutalos.
\newblock Mitochondria contribute to nadph generation in mouse rod
  photoreceptors *.
\newblock {\em Journal of Biological Chemistry}, 289:1519--1528, 01 2014.
\newblock URL: \url{https://www.jbc.org/article/S0021-9258(20)33629-2/pdf},
  \href {http://dx.doi.org/10.1074/jbc.M113.511295}
  {\path{doi:10.1074/jbc.M113.511295}}.


Fix links for doi aware entries, 
 2065  history >> hist/hist_doing_bomtex
 2228  history >> hist/hist_doing_bomtex 
 2410  history >> hist/hist_doing_bomtex 
 2513  history >> hist/hist_doing_bomtex 
 2686  # https://dx.doi.org/10.4137%2Fijtr.s2129
 2690  # https://dx.doi.org/10.5281/zenodo.6126333
 2691  wget -O xxx -S -v "https://dx.doi.org/10.5281/zenodo.6126333"
 2692  wget -O xxx -S -v "https://dx.doi.org/10.5281/zenodo.6126333?src=123131"



*/



template <class Tr>
class mjm_latex_bbl_writer 
{
 typedef mjm_latex_bbl_writer Myt;
 typedef typename Tr::IdxTy IdxTy;
 typedef typename Tr::D D;
 typedef typename Tr::StrTy StrTy;
 typedef typename Tr::Ss Ss;
 typedef typename Tr::IsTy IsTy;
 typedef typename Tr::OsTy OsTy;
 typedef typename Tr::Ofs Ofs;
//typedef typename Tr::FlagTy; 
// typedef typename Tr::MyBlock  MyBlock;

typedef mjm_blob<Tr>  Blob;
typedef mjm_ragged_table Ragged;
typedef Ragged::Line Line;
typedef mjm_bibtex_entry<Tr> BibEntry;
typedef mjm_bibtex_entry_map<Tr> BibMap;
typedef mjm_bibtex_entry_map<Tr> BibEntryMap;

typedef mjm_bibtex_fields<Tr> BibFields;


 typedef  mjm_bibitem_entry<Tr> BibItem;
 typedef mjm_bibitem_entry_map<Tr> BibItemMap;
 typedef mjm_latex_aux_parse<Tr> LatexAux;
typedef typename LatexAux::find_vector_type AuxFind;

typedef mjm_idiosyncratic_source_locator<Tr> IdioRL;

class _forms_class
{
enum  { ADDGUID=0 };
public:
_forms_class() { Init(); }
bool add_guid() const { return Bit(m_options, ADDGUID); } 
_forms_class &  add_guid(const bool x )  
{ SetReset(m_options,x,ADDGUID);  return *this; } 
_forms_class &  doc_guid(const StrTy & x ) {  m_guid=x; return *this; } 
const StrTy & doc_guid() const { return m_guid; } 

private:
bool Bit(const IdxTy f, const IdxTy b) const  { return  ((f>>b)&1)!=0; }
void SetReset(IdxTy & f, const bool x, const IdxTy b)
{ if (x) f|=(1<<b); else f&=~(1<<b); }

void Init()
{
m_options=0;

} 
StrTy m_guid; // a doi for the target output doc or similar to identify click throughs
IdxTy m_options;

}; // _forms_class
class _bib_result
{

public:
_bib_result() : ssp(0) {}
_bib_result(Ss & ss ) : ssp(&ss) {}
Ss & ss() { return * ssp; } 
Ss * ssp;

}; // _bib_result

//static _bib_result operator(Ss & ss ) { return _bib_result(ss); }

public:
typedef _forms_class Forms;
typedef _forms_class forms_class;
typedef _bib_result bib_result;
typedef bib_result BibResult;

mjm_latex_bbl_writer() {}
~mjm_latex_bbl_writer() {}

IdxTy make(BibResult & br, const BibEntry & be, const Forms & f=Forms())
{ return Make(br,be,f); } 

StrTy dump(const IdxTy flags=0) { return Dump(flags); }
private:
bool Bit(const IdxTy f, const IdxTy b) const  { return  ((f>>b)&1)!=0; }
// should loop over map now 
StrTy Dump(const IdxTy flags=0) {Ss ss;  return ss.str(); }
typedef typename mjm_thread_util<Tr>::mutex_vector MutexVector;

enum { MAP_MU=0 , MU_SZ};
mutable MutexVector m_mutex_vector;
void EnterSerial(const IdxTy i)const  {  m_mutex_vector.enter_serial(i ); }
void ExitSerial(const IdxTy i)const  {  m_mutex_vector.exit_serial(i ); }
//m_mutex_vector = MutexVector(MU_SZ);

/*
A typical bbl file entry. Entries can be extracted from the aux file
and produced similarly without the bst file. 

\bibitem{MitochondriaContributeNADPHLeopoldAdlerChunhe2014}
Leopold Adler, Chunhe Chen, and Yiannis Koutalos.
\newblock Mitochondria contribute to nadph generation in mouse rod
  photoreceptors *.
\newblock {\em Journal of Biological Chemistry}, 289:1519--1528, 01 2014.
\newblock URL: \url{https://www.jbc.org/article/S0021-9258(20)33629-2/pdf},
  \href {http://dx.doi.org/10.1074/jbc.M113.511295}
  {\path{doi:10.1074/jbc.M113.511295}}.

*/

class generic_bib
{

public:

// who, what, when, where ( container too ) , how( to find )


}; // generic_bib
IdxTy AddQuery(StrTy & url, const StrTy & q, const IdxTy flags)
{
const IdxTy lu=url.length();
const IdxTy lq=q.length();
const IdxTy lt=lu+lq;
char s[lt+5];
const char * u=url.c_str();
IdxTy pc=0;
IdxTy i=0;
while (i<lu)
{
const char c=u[i];
const bool add_after=(c=='#');
const bool add_before=(c=='?');
if (!add_after) { s[pc]=c; ++pc; } 
if (add_before)
{
memcpy(s+pc,q.c_str(),lq);
pc+=lq;
++i;
if (add_before){ s[pc]='&'; ++pc; } 
if (add_after) { s[pc]='#'; ++pc; } 
memcpy(s+pc,u+i,lu-i);
pc+=lu-i;
break;
}
++i;
} // i 
if (pc<lt)
{
s[pc]='?'; ++pc;
memcpy(s+pc,q.c_str(),lq);
pc+=lq;
} 
s[pc]=0;
url=s;
return 0;

} // AddQuery
class _UrlBlockCum
{
public:
bool seen(const StrTy & x) { ++m_seen[x];  return (m_seen[x]>1); } 
std::map<StrTy, IdxTy> m_seen;

}; // _UrlBlockCum
typedef _UrlBlockCum UrlBlockCum;

IdxTy AddUrlBlock(Ss & rr, const StrTy & u, const StrTy & n, UrlBlockCum & ubc, const IdxTy flags=0)
{
const bool terse=!Bit(flags,0);
IdioRL di=(u);
di.parse();
const bool seen=ubc.seen(u);
MM_ERR(" checkingurl "<<MMPR3(u,di.http(),seen))
if (seen) return 0; 
if (!di.http()) 
{
MM_ERR( " rejecting url "<<MMPR2(u,di.dump()))
 return ~0;
}
StrTy domain="WWW";
if (di.domain().length()) domain=di.domain();
Ss qq;
qq<<"   \\href {"<<u<<"}"<<CRLF;
if (terse) qq<<"  {\\path{src:"<<domain<<"}}."<<CRLF; 
else qq<<"  {\\path{src:"<<u<<"}}."<<CRLF; 
rr<<qq.str();
return 0; 
}
IdxTy How(Ss & rr, const BibEntry &  _be, const Forms & _f, const IdxTy flags)
{
//StrTy  get(const StrTy & n) { return StrTy(m_blobs[n]); } 
//const LiTy & get(const StrTy & key) const { 
BibEntry be=_be;
be.make_keys_canonical(0);
Forms f=_f;
IdxTy rc=0;
StrTy doi=be["doi"];
StrTy url=be["url"];
StrTy srcurl=be["srcurl"];
std::vector<StrTy> fields;
fields.push_back("urla");
fields.push_back("urlb");
fields.push_back("urlc");
fields.push_back("urld");
fields.push_back("URL");
fields.push_back("eprint");
fields.push_back("pdf_url");
fields.push_back("page_url");
fields.push_back("fulltext_html_url");
fields.push_back("buyurl");


StrTy gui=f.doc_guid();
 const StrTy doibaseurl="http://dx.doi.org/";
const bool add_guid=f.add_guid();
BibFields bf;
UrlBlockCum ubc;
std::map<StrTy,IdxTy> seen;
// TODO doi may include a url, need to clean it up here and
// in bibtex... 
if (doi.length())
{
StrTy gooddoi;
IdxTy drc=bf.fix_doi(gooddoi,doi,0);
//MM_ERR("  "<<MMPR2(doi,gooddoi))
if (gooddoi.length()) { // could use bf.add_qurty
IdioRL irl(gooddoi);
irl.parse();

StrTy u=(irl.maybe_doi())?(doibaseurl+gooddoi):gooddoi;
++seen[doibaseurl];
if (add_guid) AddQuery(u,gui,0);
AddUrlBlock(rr,u,StrTy("DOI"),ubc);
}
} // doi 
if (url.length()) if (seen[url]==0)
{
++seen[url];
// could use bf.add_qurty
StrTy u=url;
if (add_guid) AddQuery(u,gui,0);
AddUrlBlock(rr,u,StrTy("url"),ubc);
} // url 
if (srcurl!=url) if (srcurl.length()) if (seen[srcurl]==0)
{
++seen[srcurl];
// could use bf.add_qurty
StrTy u=srcurl;
if (add_guid) AddQuery(u,gui,0);
AddUrlBlock(rr,u,StrTy("srcurl"),ubc);
} // srcurl 
MM_LOOP(ii,fields)
{
// this should get the vector there have been dups... 
MM_ERR(MMPR(*ii))
const auto &list =be.get_list(*ii); 
MM_LOOP(jj,list)
{
//StrTy u=be[(*ii)];
// doh  
//StrTy u=be[(*jj)];
StrTy u=(*jj);
MM_ERR(MMPR4(be.name(),(*jj),u,seen[u]))
if (seen[u]==0) {
++seen[u];
if (add_guid) AddQuery(u,gui,0);
//AddUrlBlock(rr,u,(*ii));
AddUrlBlock(rr,u,(*jj),ubc);
}
} // jj 
} // ii 



#if 0
if (doi.length())
 {
  //url="http://dx.doi.org/"+doi+"?src_doc="+bomtex_src; // 10.1074/jbc.M113.511295}
  if (add_guid) url="http://dx.doi.org/"+doi+"?"+kvpqd; // 10.1074/jbc.M113.511295}
  else url="http://dx.doi.org/"+doi; // 10.1074/jbc.M113.511295}
Ss qq;
if (terse_path) qq<<"   \\href {"<<url<<"}"<<CRLF<<"  {\\path{DOI}}."<<CRLF; 
else qq<<"   \\href {"<<url<<"}"<<CRLF<<"  {\\path{doi:"<<doi<<"}}."<<CRLF; 
how=qq.str();
}
else
{
//  url="http://dx.doi.org/"+doi+"?src_doc="+bomtex_src; // 10.1074/jbc.M113.511295}
if (0==url.length()) url=srcurl;
StrTy dest;
if (add_guid) bf.add_query(dest,url,kvpqd,0);
else dest=url;
MM_ERR(MMPR3(dest,url,srcurl))
IdioRL di=(dest);
di.parse();
StrTy domain="WWW";
if (di.domain().length()) domain=di.domain();
//url=dest;
Ss qq;
if (terse_path) qq<<"   \\href {"<<dest<<"}"<<CRLF<<"  {\\path{url:"<<domain<<"}}."<<CRLF; 
else qq<<"   \\href {"<<dest<<"}"<<CRLF<<"  {\\path{url:"<<url<<"}}."<<CRLF; 
if (srcurl.length())
/// this  is  ignored  
//  qq<<" \\newblock   \\href {"<<StrTy("source")<<"}"<<CRLF<<"  {\\path{url:"<<srcurl<<"}}."<<CRLF; 
how=qq.str();
} // srcurl 
#endif


return rc;
} // How

IdxTy Make(BibResult & br, const BibEntry & be, const Forms & _f=Forms())
{
Forms f=_f;
f.doc_guid(StrTy("src_doc=\\mjmbib"));
f.add_guid(true);
Ss ss;
// needs "first of" and name title formatting etc 
StrTy name=be.name();
StrTy type=be.type();
StrTy ty=be["type"];
StrTy au=be["author"];
StrTy ed=be["editor"];
StrTy pu=be["publisher"];
StrTy ti=be["title"];
StrTy bt=be["booktitle"];
StrTy jr=be["journal"];
StrTy pa=be["page"];
StrTy da=be["date"];
StrTy yr=be["year"];
StrTy mo=be["month"];
StrTy day=be["day"];
StrTy vo=be["volume"];
StrTy is=be["issue"];
StrTy school=be["school"];
StrTy doi=be["doi"];
StrTy issn=be["issn"];
StrTy isbn=be["isbn"];
StrTy url=be["url"];
StrTy srcurl=be["srcurl"];


StrTy who=au;

StrTy what=ti;
StrTy where=jr;
Ss rr; rr<<pa;
StrTy more_where=rr.str();
StrTy when=da;
if (when=="") 
{
if ( yr.length())
{
when+=yr;
if (mo.length()) 
{
when+="-"+mo;
if (day.length()) when+="-"+day;
} // mo 
} // yr

} // when 
if (when.length()==0) when="-";

// 2022-06-24 compile complains unused
//bool add_guid=f.add_guid();
//bool terse_path=true; // f.add_guid();


StrTy bomtex_src=f.doc_guid();
StrTy how="";
StrTy kvpqd= "src_doc="+bomtex_src; // 10.1074/jbc.M113.511295}
Ss qq;
const IdxTy hrc=How(qq,be,f,0);
  // \href {http://dx.doi.org/10.1074/jbc.M113.511295}
  // {\path{doi:10.1074/jbc.M113.511295}}.
how=qq.str();
// need a function ptr but all these locals...
const bool  marchywka_simple=!true;
const bool  marchywka_two=true;
if (marchywka_simple)
{
ss<<"\\bibitem{"<<name<<"}"<<CRLF;
ss<<"{\\bf "<<au<<"}. "<<CRLF;
ss<<"\\newblock {"<<ti<<"}"<<CRLF;
ss<<"\\newblock {"<<jr<<"} "<<pa<<" "<<da<<CRLF;
ss<<"\\newblock \\url{"<<url<<"}"<<CRLF;
} // marchywka_simple
if (marchywka_two)
{
ss<<"\\bibitem{"<<name<<"}"<<CRLF;
ss<<"{\\bf "<<who<<"}. "<<CRLF;
ss<<"\\newblock {"<<what<<"}"<<CRLF;
ss<<"\\newblock {"<<where<<"} "<<more_where<<" ("<<when<<")"<<CRLF;
//ss<<"\\newblock \\url{"<<url<<"}"<<CRLF;
ss<<"\\newblock "<<CRLF;
ss<<how<<""<<CRLF;
} // marchywka_two

ss<<CRLF;
StrTy d;
BibFields bf;
IdxTy nonascii=bf.deal_with_non_ascii(d,ss.str(),0);
if (nonascii&1) MM_ERR("  non ascii "<<MMPR4(be.name(),be.source(),d,srcurl))
Ss & _ss=br.ss(); 
_ss<<d;

return 0; 
} // Make
// MEMBERS



}; // mjm_latex_bbl_writer

//////////////////////////////////////////////

template <class Tr>
class mjm_latex_bbl_writer_map : public std::map<typename Tr::StrTy, mjm_latex_bbl_writer< Tr > >  
{
 typedef mjm_latex_bbl_writer_map Myt;
typedef typename std::map<typename Tr::StrTy, mjm_latex_bbl_writer< Tr> >   Super;
 typedef typename Tr::IdxTy IdxTy;
 typedef typename Tr::D D;
 typedef typename Tr::StrTy StrTy;
 typedef typename Tr::Ss Ss;
 typedef typename Tr::IsTy IsTy;
 typedef typename Tr::OsTy OsTy;
 typedef typename Tr::Ofs Ofs;
//typedef typename Tr::FlagTy; 
// typedef typename Tr::MyBlock  MyBlock;
public:
mjm_latex_bbl_writer_map() {}
StrTy dump(const IdxTy flags=0) { return Dump(flags); }
private:
bool Bit(const IdxTy f, const IdxTy b) const  { return  ((f>>b)&1)!=0; }
// should loop over map now 
//StrTy Dump(const IdxTy flags=0) {Ss ss;  return ss.str(); }
typedef typename mjm_thread_util<Tr>::mutex_vector MutexVector;

enum { MAP_MU=0 , MU_SZ};
mutable MutexVector m_mutex_vector;
void EnterSerial(const IdxTy i)const  {  m_mutex_vector.enter_serial(i ); }
void ExitSerial(const IdxTy i)const  {  m_mutex_vector.exit_serial(i ); }
//m_mutex_vector = MutexVector(MU_SZ);


//StrTy dump(const IdxTy flags=0) { return Dump(flags); }

private:

void Init()
{
}

StrTy Dump(const IdxTy flags=0)
{
Ss ss;
MM_LOOP(ii,(*this))
{
ss<<(*ii).first<<CRLF;
ss<<(*ii).second.dump()<<CRLF;


}
return ss.str();
// return Dump(flags); 

}




private:

}; // mjm_latex_bbl_writer_map




////////////////////////////////////////////
#ifdef  TEST_MJM_LATEX_BBL_WRITER
class Tr {
public:
// typedef mjm_string_picker Myt;
 typedef unsigned int IdxTy;
 typedef double  D;
 typedef std::string StrTy;
 typedef std::stringstream Ss;
 typedef std::istream  IsTy;
 typedef std::ostream  OsTy;
 typedef std::ofstream  Ofs;
// typedef typename Tr::MyBlock  MyBlock;
}; // 


#include "mjm_instruments.h"
#include "mjm_cli_ui.h"
typedef Tr::StrTy StrTy;
typedef Tr::IdxTy IdxTy;

template <class Tt> class tester_ {
typedef tester_<Tt> Myt;
typedef mjm_cli_ui<Myt> Cli;
//typedef tester Myt;
//typedef mjm_cli_ui<Myt> Cli;
typedef std::map<StrTy, StrTy> LocalVar;

typedef CommandInterpretterParam Cip ;
typedef void (Myt:: * CmdFunc)(Cip &, LocalVar &  ) ;
typedef std::map<StrTy, CmdFunc> CmdMap;
typedef std::vector<StrTy> Choices;
//typedef void (Myt:: * CompleteFunc) ( Cli::list_type & choices,  const char * cmd, const char * frag);
typedef void (Myt:: * CompleteFunc) ( Choices & choices,  const char * cmd, const char * frag);
typedef std::map<StrTy, CompleteFunc> CompMap;

public:
 //void cli_cmd( Cli::list_type & choices,  const char * frag)
 void cli_cmd( Choices & choices,  const char * frag)
{
const IdxTy nfrag=strlen(frag);
MM_LOOP(ii,m_cmd_map)
{
const StrTy & v=(*ii).first;
if (strncmp(v.c_str(),frag,nfrag)==0)  choices.push_back(v);
}
}

 //void cli_param( Cli::list_type & choices,  const char * _cmd, const char * frag)
 void cli_param( Choices & choices,  const char * _cmd, const char * frag)
{
MM_ERR("cli_param"<<MMPR2(_cmd,frag))
//const StrTy cmd=CliTy::word(StrTy(_cmd),0);
//auto ii=m_comp_map.find(cmd);
//if ( ii!=m_comp_map.end()) ((this)->*(*ii).second)(choices,cmd.c_str(),frag);
}

CmdMap m_cmd_map;


 }; // tester_
typedef tester_< mjm_latex_bbl_writer <Tr>  > tester;

typedef mjm_cli_ui<tester> Cli;


typedef Tr::Ss Ss;
void about()
{
Ss ss;
ss<<" MJM_LATEX_BBL_WRITER "<<__DATE__<<" "<<__TIME__<<CRLF;
MM_ERR(ss.str())

}

int main(int argc,char **args)
{
about();
typedef mjm_latex_bbl_writer<Tr>  Myt;
//Myt x(argc,args);
Myt x;

//if (!x.done()) x.command_mode();
Cli cli;
tester tester;
CommandInterpretter li(&std::cin);
li.push(args,argc);
cli.set_target(tester);
cli.set_command_handler(&tester::cli_cmd);
cli.set_param_handler(&tester::cli_param);
cli.activate();
li.set_split(1,' ');
while (li.nextok())
{
const IdxTy sz=li.size();
if (sz<1) continue;
const StrTy cmd=li.word(0);
if (cmd=="") continue;
if (cmd=="about"){ about();  continue; } 
CommandInterpretterParam  cip(li);

if (cmd=="quit") break;
if (cmd=="dump") { MM_ERR(x.dump()) }
//else if (cmd=="load") { x.load(li.words(),1); }
//else if (cmd=="clear") { x.clear(); }

} // nextok

//if (!x.done()) x.command_mode();
return 0;
}

#endif // main

#endif // MJM_LATEX_BBL_WRITER_H__ 

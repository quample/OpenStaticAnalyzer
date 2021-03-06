/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

#include "../inc/NullLiteralWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> NullLiteralWrapper::constructor;

void NullLiteralWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "NullLiteralWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPath", setPath);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLine", setLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCol", setCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndLine", setEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndCol", setEndCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideLine", setWideLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideCol", setWideCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndLine", setWideEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndCol", setWideEndCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRaw", setRaw);
                                                                           
  constructor.Reset(isolate, tpl->GetFunction());                          
  exports->Set(v8::String::NewFromUtf8(isolate, "NullLiteralWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void NullLiteralWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new NullLiteralWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    NullLiteralWrapper* obj = new NullLiteralWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `NullLiteralWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


NullLiteralWrapper::NullLiteralWrapper(Factory* fact)                        
{                                                   
  NullLiteral = fact->getFactory()->createNullLiteralNode();          
}                                                   

NullLiteralWrapper::~NullLiteralWrapper()
{        
}        

void NullLiteralWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void NullLiteralWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  NullLiteralWrapper* _NullLiteral2 = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());

  _NullLiteral2->NullLiteral->addComments(_Comment1->Comment);
}
void NullLiteralWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _NullLiteral->NullLiteral->getPosition();
  range.setPath( param );
  _NullLiteral->NullLiteral->setPosition( range );
}

void NullLiteralWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NullLiteral->NullLiteral->getPosition();
  range.setLine( ui );
  _NullLiteral->NullLiteral->setPosition( range );
}

void NullLiteralWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NullLiteral->NullLiteral->getPosition();
  range.setCol( ui );
  _NullLiteral->NullLiteral->setPosition( range );
}

void NullLiteralWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NullLiteral->NullLiteral->getPosition();
  range.setEndLine( ui );
  _NullLiteral->NullLiteral->setPosition( range );
}

void NullLiteralWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NullLiteral->NullLiteral->getPosition();
  range.setEndCol( ui );
  _NullLiteral->NullLiteral->setPosition( range );
}

void NullLiteralWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NullLiteral->NullLiteral->getPosition();
  range.setWideLine( ui );
  _NullLiteral->NullLiteral->setPosition( range );
}

void NullLiteralWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NullLiteral->NullLiteral->getPosition();
  range.setWideCol( ui );
  _NullLiteral->NullLiteral->setPosition( range );
}

void NullLiteralWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NullLiteral->NullLiteral->getPosition();
  range.setWideEndLine( ui );
  _NullLiteral->NullLiteral->setPosition( range );
}

void NullLiteralWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _NullLiteral->NullLiteral->getPosition();
  range.setWideEndCol( ui );
  _NullLiteral->NullLiteral->setPosition( range );
}

void NullLiteralWrapper::setRaw(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  NullLiteralWrapper* _NullLiteral = ObjectWrap::Unwrap<NullLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  _NullLiteral->NullLiteral->setRaw( param );
}
}}}} //end of namespaces
////////////////////////////////////////////////////////////////////////////////
//
//  ADOBE SYSTEMS INCORPORATED
//  Copyright 2005-2007 Adobe Systems Incorporated
//  All Rights Reserved.
//
//  NOTICE: Adobe permits you to use, modify, and distribute this file
//  in accordance with the terms of the license agreement accompanying it.
//
////////////////////////////////////////////////////////////////////////////////

package mx.messaging.messages
{

[RemoteClass(alias="flex.messaging.messages.ErrorMessage")]

/**
 *  The ErrorMessage class is used to report errors within the messaging system.
 *  An error message only occurs in response to a message sent within the
 *  system.
 *  
 *  @langversion 3.0
 *  @playerversion Flash 9
 *  @playerversion AIR 1.1
 *  @productversion BlazeDS 4
 *  @productversion LCDS 3 
 */
public class ErrorMessage extends AcknowledgeMessage
{
    //--------------------------------------------------------------------------
    //
    // Static Constants
    // 
    //--------------------------------------------------------------------------

    /**
     *  If a message may not have been delivered, the <code>faultCode</code> will
     *  contain this constant. 
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion BlazeDS 4
     *  @productversion LCDS 3 
     */ 
    public static const MESSAGE_DELIVERY_IN_DOUBT:String = "Client.Error.DeliveryInDoubt";
     
    /**
     *  Header name for the retryable hint header.
     *  This is used to indicate that the operation that generated the error
     *  may be retryable rather than fatal.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion BlazeDS 4
     *  @productversion LCDS 3 
     */
    public static const RETRYABLE_HINT_HEADER:String = "DSRetryableErrorHint";

    //--------------------------------------------------------------------------
    //
    // Constructor
    // 
    //--------------------------------------------------------------------------
    
    /**
     *  Constructs an ErrorMessage instance.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion BlazeDS 4
     *  @productversion LCDS 3 
     */
    public function ErrorMessage()
    {
        super();
    }

    //--------------------------------------------------------------------------
    //
    // Variables
    // 
    //--------------------------------------------------------------------------

    /**
     *  The fault code for the error.
     *  This value typically follows the convention of
     *  "[outer_context].[inner_context].[issue]".
     *  For example: "Channel.Connect.Failed", "Server.Call.Failed", etc.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion BlazeDS 4
     *  @productversion LCDS 3 
     */
    public var faultCode:String;

    /**
     *  A simple description of the error.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion BlazeDS 4
     *  @productversion LCDS 3 
     */
    public var faultString:String;

    /**
     *  Detailed description of what caused the error.
     *  This is typically a stack trace from the remote destination.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion BlazeDS 4
     *  @productversion LCDS 3 
     */
    public var faultDetail:String;

    /**
     *  Should a root cause exist for the error, this property contains those details.
     *  This may be an ErrorMessage, a NetStatusEvent info Object, or an underlying
     *  Flash error event: ErrorEvent, IOErrorEvent, or SecurityErrorEvent.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion BlazeDS 4
     *  @productversion LCDS 3 
     */
    public var rootCause:Object;
    
    /**
     * Extended data that the remote destination has chosen to associate
     * with this error to facilitate custom error processing on the client.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion BlazeDS 4
     *  @productversion LCDS 3 
     */
    public var extendedData:Object;


    //--------------------------------------------------------------------------
    //
    // Overridden Methods
    // 
    //--------------------------------------------------------------------------

    /**
     * @private
     */
    override public function getSmallMessage():IMessage
    {
        return null;
    }
}

}
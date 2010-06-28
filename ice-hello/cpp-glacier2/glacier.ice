module Glacier2 {
    exception PermissionDeniedException {
        string reason;
    };

    interface Router extends Ice::Router {
      Session* createSession(string userId, string password)
            throws PermissionDeniedException, CannotCreateSessionException;

      Session* createSessionFromSecureConnection()
          throws PermissionDeniedException, CannotCreateSessionException;

      idempotent string getCategoryForClient();

      idempotent long getSessionTimeout();

      void destroySession()
          throws SessionNotExistException;
   };
};
